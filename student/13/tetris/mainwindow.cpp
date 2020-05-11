#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lcdNumberSec->setStyleSheet("background-color: red");
    ui->lcdNumberMin->setStyleSheet("background-color: blue");
    ui->lcdNumberScore->setStyleSheet("background-color: white");

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
    minTimer_.setSingleShot(false);
    connect(&minTimer_, &QTimer::timeout, this, &MainWindow::timeKeeping);

    //circle_ = scene_->addRect(0, 0, STEP, STEP, blackPen, redBrush);

    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::dropStuff);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::scoreKeeping);

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    for (int i=0; i<NUMBER_OF_TETROMINOS; i++){
        tetrominos_.push_back({colours_[i], y_[i],x_[i]});
    }


    // Add more initial settings and connect calls, when needed.
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{

    //scene_->clear();
    for (auto c : blocks_){
        scene_->removeItem(c);
        }
    blocks_.clear();

    ui->startButton->setEnabled(false);
    ui->ClosepushButton->setEnabled(false);
    //scene_->clear();

    score_= 0;
    min_=0;
    sec_=0;
    ui->lcdNumberScore->display(score_);
    ui->lcdNumberSec->display(sec_);
     ui->lcdNumberMin->display(min_);

    builder();
    minTimer_.start(speed_);
    timer_.start(1000);


    //dropStuff();
}

void MainWindow::dropStuff()
{
    bool moveable = true;
    for (auto c : active_){
        if(!(isValid(c, 0, STEP))){
               moveable = false;
        }
    }

    if (moveable){
        for (auto c : active_){
            qreal current_y = c->y();
            qreal deltaY;

            deltaY = static_cast<qreal>(STEP);  // down (positive step)
            current_y += deltaY;
            c->moveBy(0, deltaY);
        }

    } else {
        for (auto &c : active_){
            blocks_.push_back(c);
            }
        active_.clear();

        if(isGameOver()){
            minTimer_.stop();
            timer_.stop();
            QMessageBox Msgbox;
                Msgbox.setText("Game has bloody ended okay");
                Msgbox.exec();
                ui->ClosepushButton->setEnabled(true);
                ui->startButton->setEnabled(true);
                speed_ = 1000;

        } else{
            if(speed_ > 50){
                speed_ -= 20;
            }
            //lineClear();
            timer_.setInterval(speed_);
            builder();
        }
    }
}

void MainWindow::builder()
{

    int choice = distr(randomEng);
    //int choice = 0;

    QBrush fill(tetrominos_.at(choice).colour);
    QPen outline(Qt::black);
    outline.setWidth(2);

    current_ = choice;

    for (int i=0; i<4; i++){

        int x_off = tetrominos_.at(choice).x_offset.at(i);
        int y_off = tetrominos_.at(choice).y_offset.at(i);

        circle_ = scene_->addRect(0, 0, STEP, STEP, outline, fill);

        circle_->moveBy(i*STEP+ STEP*4 + x_off*STEP, STEP + y_off*STEP);
        active_.push_back(circle_);
        rotation_ = 1;
    }

}

bool MainWindow::isValid(QGraphicsRectItem* block, int horizontal, int vertical)
{

    qreal current_y = block->y();
    qreal current_x = block->x();
    qreal deltaX;
    qreal deltaY;

    deltaX = static_cast<qreal>(horizontal); // side movement
    current_x += deltaX;

    deltaY = static_cast<qreal>(vertical);  // down
    current_y += deltaY;

    if(current_x <= -20 || current_x >= 240){ // is inside game border horizontally
        return false;
    }

    if (!(current_y <= 460)){ // is inside game border vertically
        return false;
    }

    for (auto block : blocks_){
        qreal test_y = block->y();
        qreal test_x = block->x();

        if (test_y == current_y && test_x == current_x){
            return false;
        }
    }
    return true;
}

void MainWindow::lineClear()
{
    std::vector<qreal> coords;
    //std::vector<QGraphicsRectItem*> temp;

    for(auto &block : blocks_){
        coords.push_back(block->y());
        }

    std::unordered_map<unsigned, size_t> counts;
    for (auto v : coords)
        ++counts[v];

    for (auto const &p : counts){
        if(p.second==12){

            for (auto &block : blocks_){

                if(block->y()==p.first){

                    scene_->removeItem(block);
                    blocks_.removeOne(block);
                    block = nullptr;
                    }
            }
            for (auto &block : blocks_){

                if (block->y()<p.first){
                    block->moveBy(0,STEP);
                }
            }

        }

    }

}

void MainWindow::rotate(int fallingBlock)
{
    if (fallingBlock == HORIZONTAL){

        if (rotation_== 1 && isValid(active_[0],STEP*2,-STEP*2)&& isValid(active_[1],STEP,-STEP)&& isValid(active_[3],-STEP,STEP)){
            active_[0]->moveBy(STEP*2,-STEP*2);
            active_[1]->moveBy(STEP,-STEP);
            active_[3]->moveBy(-STEP,STEP);
            rotation_++;

        } else if(rotation_== 2 && isValid(active_[0],-2*STEP,2*STEP)&& isValid(active_[1],-STEP,STEP)&& isValid(active_[3],STEP,-STEP)){
            active_[0]->moveBy(-2*STEP,2*STEP);
            active_[1]->moveBy(-STEP,STEP);

            active_[3]->moveBy(STEP,-STEP);
            rotation_=1;
        }

    } else if (fallingBlock == LEFT_CORNER){

        if (rotation_== 1 && isValid(active_[0],STEP,-STEP)&& isValid(active_[2],-STEP,STEP)&& isValid(active_[3],STEP*2,0)){
            active_[0]->moveBy(STEP,-STEP);
            active_[2]->moveBy(-STEP,STEP);
            active_[3]->moveBy(STEP*2,0);
            rotation_++;

        } else if(rotation_== 2 && isValid(active_[0],STEP,STEP)&& isValid(active_[2],-STEP,-STEP)&& isValid(active_[3],0,STEP*2)){
            active_[0]->moveBy(STEP,STEP);
            active_[2]->moveBy(-STEP,-STEP);
            active_[3]->moveBy(0,STEP*2);
            rotation_++;

        } else if(rotation_== 3 && isValid(active_[0],-STEP,STEP)&& isValid(active_[2],STEP,-STEP)&& isValid(active_[3],-2*STEP,0)){
            active_[0]->moveBy(-STEP,STEP);
            active_[2]->moveBy(STEP,-STEP);
            active_[3]->moveBy(-2*STEP,0);
            rotation_++;

        } else if(rotation_== 4 && isValid(active_[0],-STEP,-STEP)&& isValid(active_[2],STEP,STEP)&& isValid(active_[3],0,-2*STEP)){
            active_[0]->moveBy(-STEP,-STEP);
            active_[2]->moveBy(STEP,STEP);
            active_[3]->moveBy(0,-2*STEP);
            rotation_= 1;
        }

    } else if (fallingBlock == RIGHT_CORNER){

        if (rotation_== 1 && isValid(active_[0],STEP,-STEP)&& isValid(active_[2],-STEP,STEP)&& isValid(active_[3],0,STEP*2)){
            active_[0]->moveBy(STEP,-STEP);
            active_[2]->moveBy(-STEP,STEP);
            active_[3]->moveBy(0,STEP*2);
            rotation_++;

        } else if(rotation_== 2 && isValid(active_[0],STEP,STEP)&& isValid(active_[2],-STEP,-STEP)&& isValid(active_[3],-STEP*2,0)){
            active_[0]->moveBy(STEP,STEP);
            active_[2]->moveBy(-STEP,-STEP);
            active_[3]->moveBy(-STEP*2,0);
            rotation_++;

        } else if(rotation_== 3 && isValid(active_[0],-STEP,STEP)&& isValid(active_[2],STEP,-STEP)&& isValid(active_[3],0,-2*STEP)){
            active_[0]->moveBy(-STEP,STEP);
            active_[2]->moveBy(STEP,-STEP);
            active_[3]->moveBy(0,-2*STEP);
            rotation_++;

        } else if(rotation_== 4 && isValid(active_[0],-STEP,-STEP)&& isValid(active_[2],STEP,STEP)&& isValid(active_[3],2*STEP,0)){
            active_[0]->moveBy(-STEP,-STEP);
            active_[2]->moveBy(STEP,STEP);
            active_[3]->moveBy(2*STEP,0);
            rotation_= 1;
        }

    } else if (fallingBlock == STEP_UP_RIGHT){

        if (rotation_== 1 && isValid(active_[2],-STEP,0)&& isValid(active_[3],-STEP,STEP*2)){
            active_[2]->moveBy(-STEP,0);
            active_[3]->moveBy(-STEP,STEP*2);
            rotation_++;

        } else if(rotation_== 2 && isValid(active_[2],STEP,0)&& isValid(active_[3],STEP,STEP*-2)){
            active_[2]->moveBy(STEP,0);
            active_[3]->moveBy(STEP,STEP*-2);
            rotation_=1;
        }

    } else if (fallingBlock == PYRAMID){

        if (rotation_== 1 && isValid(active_[2],-STEP,STEP)){
            active_[0]->moveBy(STEP,-STEP);
            active_[3]->moveBy(STEP,STEP);
            active_[2]->moveBy(-STEP,STEP);
            rotation_++;

        } else if(rotation_== 2 && isValid(active_[2],-STEP,-STEP)){
            active_[0]->moveBy(STEP,STEP);
            active_[3]->moveBy(-STEP,STEP);
            active_[2]->moveBy(-STEP,-STEP);
            rotation_++;
        } else if(rotation_== 3 && isValid(active_[2],STEP,-STEP)){
            active_[0]->moveBy(-STEP,STEP);
            active_[3]->moveBy(-STEP,-STEP);
            active_[2]->moveBy(STEP,-STEP);
            rotation_++;
        } else if(rotation_== 4 && isValid(active_[3],STEP,STEP)){
            active_[0]->moveBy(-STEP,-STEP);
            active_[3]->moveBy(STEP,-STEP);
            active_[2]->moveBy(STEP,STEP);
            rotation_=1;
        }

    } else if (fallingBlock == STEP_UP_LEFT){

        if (rotation_== 1 && isValid(active_[0],STEP,STEP*2)&& isValid(active_[3],STEP,0)){
            active_[0]->moveBy(STEP,STEP*2);
            active_[3]->moveBy(STEP,0);
            rotation_++;

        } else if(rotation_== 2 && isValid(active_[0],-STEP,-STEP*2)&& isValid(active_[3],-STEP,0)){
            active_[0]->moveBy(-STEP,-STEP*2);
            active_[3]->moveBy(-STEP,0);
            rotation_=1;
        }

    }
}

void MainWindow::timeKeeping()
{
    sec_ += 1;
    if (sec_ >= 60){
        min_ += 1;
        sec_ = 0;
    }
    ui->lcdNumberSec->display(sec_);
     ui->lcdNumberMin->display(min_);

}

void MainWindow::scoreKeeping()
{
    score_ += 10/timer_.interval();
    //score_ += 10;
    ui->lcdNumberScore->display(score_);
}

bool MainWindow::isGameOver()
{

    for (auto block : blocks_){
        if (block->y() == 0){
            return true;
        }
    }
    return false;

}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if( event->key() == Qt::Key_D){
        horizontalMovement(STEP);
    } else if(event->key()== Qt::Key_A){
        horizontalMovement(-STEP);
    } else if(event->key() == Qt::Key_S){
        timer_.setInterval(1);
    } else if(event->key()== Qt::Key_E){
        rotate(current_);
    }
}

void MainWindow::horizontalMovement(int dir)
{
    bool moveable = true;

    for (auto c : active_){
        if(!(isValid(c, dir,0))){
               moveable = false;
        }
    }

    if (moveable){
         for (auto c : active_){
             qreal deltaX;

             deltaX = static_cast<qreal>(dir);  // LEFT
              c->moveBy(deltaX, 0);
         }
    }

}


