#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <random>
#include <QTimer>
#include <QKeyEvent>
#include <vector>
#include <map>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_dropButton_clicked();

    void on_RightpushButton_clicked();

    void on_leftPushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_;
    QGraphicsRectItem* circle_;

    QGraphicsItem* why_;
    //QGraphicsEllipseItem* circle2_;
    QTimer timer_;

    // Constants describing scene coordinates
    // Copied from moving circle example and modified a bit
    const int STEP = 20;
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)


    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HORIZONTAL,
                         LEFT_CORNER,
                         RIGHT_CORNER,
                         SQUARE,
                         STEP_UP_RIGHT,
                         PYRAMID,
                         STEP_UP_LEFT,
                         NUMBER_OF_TETROMINOS};
    // From the enum values above, only the last one is needed in this template.
    // Recall from enum type that the value of the first enumerated value is 0,
    // the second is 1, and so on.
    // Therefore the value of the last one is 7 at the moment.
    // Remove those tetromino kinds above that you do not implement,
    // whereupon the value of NUMBER_OF_TETROMINOS changes, too.
    // You can also remove all the other values, if you do not need them,
    // but most probably you need a constant value for NUMBER_OF_TETROMINOS.

    struct Tetro_{
        QColor col;
        std::vector<int> y_offset;
        std::vector<int> x_offset;
    };


    std::vector<QColor> colours_ = {
                                Qt::cyan ,
                                Qt::blue ,
                                Qt::gray,
                                Qt::yellow ,
                                Qt::green ,
                                Qt::magenta ,
                                Qt::red ,
                                };

   std::vector<std::vector<int>> x_ = {
                       {  0, 0, 0, 0 },
                       {  0, 0, 0, -3 },
                       {  0, 0, 0, -1 },
                       {  0, 0, -2, -2 },
                       {  0, 0, -1, -1 },
                       {  0, 0, 0, -2 },
                       {  0, 0, 0, -2},
                                    };
   std::vector<std::vector<int>> y_ = {
                       {  0, 0, 0, 0 },
                       {  0, 0, 0, -1 },
                       {  0, 0, 0, -1 },
                       {  0, 0, -1, -1 },
                       {  0, 0, -1, -1 },
                       {  0, 0, 0, -1 },
                       {  -1, 0, 0, -1 },
                                    };

    std::vector<Tetro_> noice_;

    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    void dropStuff();
    std::vector<QGraphicsRectItem*> blocks_;
    std::vector<QGraphicsRectItem*> active_;
    void builder();
    // More constants, attibutes, and methods
};

#endif // MAINWINDOW_HH
