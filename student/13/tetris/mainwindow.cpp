#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lcdNumberSec->setStyleSheet("background-color: red");
    ui->lcdNumberMin->setStyleSheet("background-color: blue");
    ui->lcdNumberScore->setStyleSheet("background-color: white");

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
        BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // minute timer initialized and connected with minute/second clock
    minTimer_.setSingleShot(false);
    connect(&minTimer_, &QTimer::timeout, this, &MainWindow::timeKeeping);

    // timer for block fall speed and score initialized
    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::verticalMovement);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::scoreKeeping);

    // Setting random engine ready for the first real call.
    int seed = time(0);
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)

    // creating each tetromino
    for (int i = 0; i < NUMBER_OF_TETROMINOS; i++) {
        tetrominos_.push_back({ colours_[i], y_[i], x_[i] });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    clearPrevious();

    ui->startButton->setEnabled(false);
    ui->ClosepushButton->setEnabled(false);

    builder();
    minTimer_.start(speed_);
    timer_.start(1000);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_D) {
        horizontalMovement(STEP);
    }
    else if (event->key() == Qt::Key_A) {
        horizontalMovement(-STEP);
    }
    else if (event->key() == Qt::Key_S) {
        timer_.setInterval(FAST_DROP);
    }
    else if (event->key() == Qt::Key_W && current_>=0) {
        rotate(current_);
    }
}

void MainWindow::builder()
{

    int choice = distr(randomEng);

    QBrush fill(tetrominos_.at(choice).colour);
    QPen outline(Qt::black);
    outline.setWidth(2);

    current_ = choice;

    for (int i = 0; i < 4; i++) {

        int x_off = tetrominos_.at(choice).x_offset.at(i);
        int y_off = tetrominos_.at(choice).y_offset.at(i);

        square_ = scene_->addRect(0, 0, STEP, STEP, outline, fill);

        //Creating it 2 steps "outside" the grid so it does not spawn on a block
        square_->moveBy(i * STEP + STEP * 4 + x_off * STEP, -STEP + y_off * STEP);
        active_.push_back(square_);
        rotation_ = UP;
    }

    // moving to correct start position
    verticalMovement();
    verticalMovement();
}

bool MainWindow::isValid(QGraphicsRectItem* block, int horizontal, int vertical)
{

    qreal current_y = block->y();
    qreal current_x = block->x();
    qreal deltaX;
    qreal deltaY;

    deltaX = static_cast<qreal>(horizontal); // side movement
    current_x += deltaX;

    deltaY = static_cast<qreal>(vertical); // down
    current_y += deltaY;

    if (current_x <= -20 || current_x >= 240) { // is inside game border horizontally
        return false;
    }

    if (!(current_y <= 460)) { // is inside game border vertically
        return false;
    }

    for (auto block : static_) {
        qreal test_y = block->y();
        qreal test_x = block->x();

        // if is on another (static) block
        if (test_y == current_y && test_x == current_x) {
            return false;
        }
    }
    return true;
}

void MainWindow::horizontalMovement(int dir)
{
    bool moveable = true;

    for (auto block : active_) {
        if (!(isValid(block, dir, 0))) {
            moveable = false;
        }
    }

    if (moveable) {
        for (auto block : active_) {
            block->moveBy(dir, 0);
        }
    }
}

void MainWindow::verticalMovement()
{
    bool moveable = true;
    for (auto block : active_) {
        if (!(isValid(block, 0, STEP))) {
            moveable = false;
        }
    }

    if (moveable) {
        for (auto block : active_) {
            block->moveBy(0, STEP);
        }
    }
    else {
        anchorBlocks();
    }
}

void MainWindow::anchorBlocks()
{
    for (auto block : active_) {
        static_.push_back(block);
    }
    active_.clear();

    if (isGameOver()) {
        minTimer_.stop();
        timer_.stop();
        gameHasEnded();
        current_= -1;
    }
    else {

        if (speed_ > 50) {
            speed_ -= 20;
            timer_.setInterval(speed_);
        }

        builder();
    }
}

void MainWindow::rotate(int& fallingBlock)
{

    if (fallingBlock == HORIZONTAL) {

        if (rotation_ == UP &&
            isValid(active_[1], -STEP, STEP) &&
            isValid(active_[2], -STEP * 2, STEP * 2) &&
            isValid(active_[3], -STEP * 3, STEP * 3)) {

            active_[1]->moveBy(-STEP, STEP);
            active_[2]->moveBy(-STEP * 2, STEP * 2);
            active_[3]->moveBy(-STEP * 3, STEP * 3);
            rotation_ = DOWN;
        }
        else if (rotation_ == DOWN &&
                 isValid(active_[1], STEP, -STEP) &&
                 isValid(active_[2], STEP * 2, -STEP * 2) &&
                 isValid(active_[3], STEP * 3, -STEP * 3)) {

            active_[1]->moveBy(STEP, -STEP);
            active_[2]->moveBy(STEP * 2, -STEP * 2);
            active_[3]->moveBy(STEP * 3, -STEP * 3);
            rotation_ = UP;
        }
    }
    else if (fallingBlock == LEFT_CORNER) {

        if (rotation_ == UP &&
            isValid(active_[0], STEP, -STEP) &&
            isValid(active_[2], -STEP, STEP) &&
            isValid(active_[3], STEP * 2, 0)) {

            active_[0]->moveBy(STEP, -STEP);
            active_[2]->moveBy(-STEP, STEP);
            active_[3]->moveBy(STEP * 2, 0);
            rotation_ = LEFT;
        }
        else if (rotation_ == LEFT &&
                 isValid(active_[0], STEP, STEP) &&
                 isValid(active_[2], -STEP, -STEP) &&
                 isValid(active_[3], 0, STEP * 2)) {

            active_[0]->moveBy(STEP, STEP);
            active_[2]->moveBy(-STEP, -STEP);
            active_[3]->moveBy(0, STEP * 2);
            rotation_ = DOWN;
        }
        else if (rotation_ == DOWN &&
                 isValid(active_[0], -STEP, STEP) &&
                 isValid(active_[2], STEP, -STEP) &&
                 isValid(active_[3], 2 * -STEP, 0)) {

            active_[0]->moveBy(-STEP, STEP);
            active_[2]->moveBy(STEP, -STEP);
            active_[3]->moveBy(2 * -STEP, 0);
            rotation_ = RIGHT;
        }
        else if (rotation_ == RIGHT &&
                 isValid(active_[0], -STEP, -STEP) &&
                 isValid(active_[2], STEP, STEP) &&
                 isValid(active_[3], 0, 2 * -STEP)) {

            active_[0]->moveBy(-STEP, -STEP);
            active_[2]->moveBy(STEP, STEP);
            active_[3]->moveBy(0, 2 * -STEP);
            rotation_ = UP;
        }
    }
    else if (fallingBlock == RIGHT_CORNER) {

        if (rotation_ == UP &&
            isValid(active_[0], STEP, -STEP) &&
            isValid(active_[2], -STEP, STEP) &&
            isValid(active_[3], 0, STEP * 2)) {

            active_[0]->moveBy(STEP, -STEP);
            active_[2]->moveBy(-STEP, STEP);
            active_[3]->moveBy(0, STEP * 2);
            rotation_ = LEFT;
        }
        else if (rotation_ == LEFT &&
                 isValid(active_[0], STEP, STEP) &&
                 isValid(active_[2], -STEP, -STEP) &&
                 isValid(active_[3], -STEP * 2, 0)) {

            active_[0]->moveBy(STEP, STEP);
            active_[2]->moveBy(-STEP, -STEP);
            active_[3]->moveBy(-STEP * 2, 0);
            rotation_ = DOWN;
        }
        else if (rotation_ == DOWN &&
                 isValid(active_[0], -STEP, STEP) &&
                 isValid(active_[2], STEP, -STEP) &&
                 isValid(active_[3], 0, 2 * -STEP)) {

            active_[0]->moveBy(-STEP, STEP);
            active_[2]->moveBy(STEP, -STEP);
            active_[3]->moveBy(0, 2 * -STEP);
            rotation_ = RIGHT;
        }
        else if (rotation_ == RIGHT &&
                 isValid(active_[0], -STEP, -STEP) &&
                 isValid(active_[2], STEP, STEP) &&
                 isValid(active_[3], 2 * STEP, 0)) {

            active_[0]->moveBy(-STEP, -STEP);
            active_[2]->moveBy(STEP, STEP);
            active_[3]->moveBy(2 * STEP, 0);
            rotation_ = UP;
        }
    }
    else if (fallingBlock == STEP_UP_RIGHT) {

        if (rotation_ == UP &&
                isValid(active_[2], -STEP, 0) &&
                isValid(active_[3], -STEP, STEP * 2)) {

            active_[2]->moveBy(-STEP, 0);
            active_[3]->moveBy(-STEP, STEP * 2);
            rotation_ = LEFT;
        }
        else if (rotation_ == LEFT &&
                 isValid(active_[2], STEP, 0) &&
                 isValid(active_[3], STEP, STEP * -2)) {

            active_[2]->moveBy(STEP, 0);
            active_[3]->moveBy(STEP, STEP * -2);
            rotation_ = UP;
        }
    }
    else if (fallingBlock == PYRAMID) {

        if (rotation_ == UP && isValid(active_[2], -STEP, STEP)) {

            active_[0]->moveBy(STEP, -STEP);
            active_[3]->moveBy(STEP, STEP);
            active_[2]->moveBy(-STEP, STEP);
            rotation_ = LEFT;
        }
        else if (rotation_ == LEFT && isValid(active_[2], -STEP, -STEP)) {

            active_[0]->moveBy(STEP, STEP);
            active_[3]->moveBy(-STEP, STEP);
            active_[2]->moveBy(-STEP, -STEP);
            rotation_ = DOWN;
        }
        else if (rotation_ == DOWN && isValid(active_[2], STEP, -STEP)) {

            active_[0]->moveBy(-STEP, STEP);
            active_[3]->moveBy(-STEP, -STEP);
            active_[2]->moveBy(STEP, -STEP);
            rotation_ = RIGHT;
        }
        else if (rotation_ == RIGHT && isValid(active_[3], STEP, STEP)) {

            active_[0]->moveBy(-STEP, -STEP);
            active_[3]->moveBy(STEP, -STEP);
            active_[2]->moveBy(STEP, STEP);
            rotation_ = UP;
        }
    }
    else if (fallingBlock == STEP_UP_LEFT) {

        if (rotation_ == UP &&
            isValid(active_[0], STEP, STEP * 2) &&
            isValid(active_[3], STEP, 0)) {

            active_[0]->moveBy(STEP, STEP * 2);
            active_[3]->moveBy(STEP, 0);
            rotation_ = LEFT;
        }
        else if (rotation_ == LEFT &&
                 isValid(active_[0], -STEP, -STEP * 2) &&
                 isValid(active_[3], -STEP, 0)) {

            active_[0]->moveBy(-STEP, -STEP * 2);
            active_[3]->moveBy(-STEP, 0);
            rotation_ = UP;
        }
    }
}

void MainWindow::timeKeeping()
{
    sec_++;
    if (sec_ >= 60) {
        min_++;
        sec_ = 0;
    }

    ui->lcdNumberSec->display(sec_);
    ui->lcdNumberMin->display(min_);
}

void MainWindow::scoreKeeping()
{
    score_ += SCORE_INTERVAL / timer_.interval();
    ui->lcdNumberScore->display(score_);
}

bool MainWindow::isGameOver()
{

    for (auto block : static_) {
        if (block->y() == 0) {
            return true;
        }
    }
    return false;
}

void MainWindow::gameHasEnded()
{
    QMessageBox Msgbox;
    Msgbox.setText("Game has ended :) \n thanks for playing");
    Msgbox.exec();
    ui->ClosepushButton->setEnabled(true);
    ui->startButton->setEnabled(true);
}

void MainWindow::clearPrevious()
{
    for (auto block : static_) {
        scene_->removeItem(block);
    }

    static_.clear();

    score_ = 0;
    min_ = 0;
    sec_ = 0;
    speed_ = INITIAL_SPEED;

    ui->lcdNumberScore->display(score_);
    ui->lcdNumberSec->display(sec_);
    ui->lcdNumberMin->display(min_);
}
