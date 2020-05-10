#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
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

    //QBrush redBrush(Qt::red);
    //QPen blackPen(Qt::black);
    //blackPen.setWidth(2);

    //circle_ = scene_->addRect(0, 0, STEP, STEP, blackPen, redBrush);

    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::dropStuff);

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    for (int i=0; i<NUMBER_OF_TETROMINOS; i++){
        noice_.push_back({colours_[i], y_[i],x_[i] });
    }
    // Add more initial settings and connect calls, when needed.
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dropButton_clicked()
{
    timer_.start(40);
    dropStuff();

}

void MainWindow::dropStuff()
{
    bool valid = true;
    for (auto c : active_){
    qreal current_y = c->y();
    qreal current_x = c->x();

    qreal deltaY;

    deltaY = static_cast<qreal>(STEP);  // down (positive step)
    current_y += deltaY;


    if (current_y <= 460){
        for (auto block : blocks_){
            qreal test_y = block->y();
            qreal test_x = block->x();

            if (test_y == current_y && test_x == current_x){
                timer_.stop();
                valid = false;

            }
        }

    } else {
        timer_.stop();
        valid = false;
        }
    }

    if (valid){
        for (auto c : active_){
            qreal current_y = c->y();

            qreal deltaY;

            deltaY = static_cast<qreal>(STEP);  // down (positive step)
            current_y += deltaY;
            c->moveBy(0, deltaY);
        }

    } else {
        for (auto c : active_){
            blocks_.push_back(c);
            }
        active_.clear();
        //builder();

    }
}

void MainWindow::builder()
{

    int choice = distr(randomEng);

    //std::string col = noice_[choice].colour;


    QBrush fill(noice_.at(choice).col);
    QPen outline(Qt::black);
    outline.setWidth(2);


    for (int i=0; i<4; i++){

        int x_off = noice_.at(choice).x_offset.at(i);
        int y_off = noice_.at(choice).y_offset.at(i);

        circle_ = scene_->addRect(0, 0, STEP, STEP, outline, fill);

        circle_->moveBy(i*STEP+40 + x_off*STEP, 0 + y_off*STEP);
        active_.push_back(circle_);
    }

}

void MainWindow::on_RightpushButton_clicked()
{
    bool moveable = true;

    for (auto c : active_){
    qreal current_y = c->y();
    qreal current_x = c->x();
    qreal deltaX;

    deltaX = static_cast<qreal>(STEP);  // RIGHT
    current_x += deltaX;

    if(current_x >= 240){
        moveable = false;
    }

    for (auto block : blocks_){
        qreal test_y = block->y();
        qreal test_x = block->x();
        if (test_y == current_y && test_x == current_x){
            moveable = false;
        }
    }


    }

    if (moveable){
         for (auto c : active_){
             qreal deltaX;

             deltaX = static_cast<qreal>(STEP);  // RIGHT
              c->moveBy(deltaX, 0);
         }
    }

}

void MainWindow::on_leftPushButton_clicked()
{
    bool moveable = true;

    for (auto c : active_){
    qreal current_y = c->y();
    qreal current_x = c->x();
    qreal deltaX;

    deltaX = static_cast<qreal>(-STEP);  // RIGHT
    current_x += deltaX;

    if(current_x <= -20){
        moveable = false;
    }

    for (auto block : blocks_){
        qreal test_y = block->y();
        qreal test_x = block->x();
        if (test_y == current_y && test_x == current_x){
            moveable = false;
        }
    }


    }

    if (moveable){
         for (auto c : active_){
             qreal deltaX;

             deltaX = static_cast<qreal>(-STEP);  // RIGHT
              c->moveBy(deltaX, 0);
         }
    }

}
void MainWindow::on_pushButton_clicked()
{
    builder();
}
