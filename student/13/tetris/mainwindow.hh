/* TETRIS
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 *
 * Program author:
 * Name: Aleksi Rissa
 * Student number: 292053
 * UserID: xfalri
 * E-Mail: aleksi.rissa@tuni.fi
 *
 *
 * Notes about the program and it's implementation:
 *
 * A tetris-like game, what gets progressively faster as the game progresses
 * Points are given if you speed up the descent of a block, and while you can
 * rotate a block, lines are not cleared. Game ends if a block reaches the top
 * row or a new block cannot be spawned.
 *
 * More notes in instructions.txt file
 *
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>
#include <random>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    /**
     * @brief on_startButton_clicked
     * When the start button is clicked,
     * starts the game and disables the buttons.
     */
    void on_startButton_clicked();

private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene_;
    QGraphicsRectItem* square_;

    // game time (for block fall speed and score keeping)
    QTimer timer_;
    // minute timer, stays constant for time keeping.
    QTimer minTimer_;

    // list of all active (moving) blocks
    QList<QGraphicsRectItem*> active_;
    // list of all stationary blocks
    QList<QGraphicsRectItem*> static_;

    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    // Constants describing scene coordinates

    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240;

    // Points per block dropped fast
    const int SCORE_INTERVAL = 10;
    //initial speed of blocks
    const int INITIAL_SPEED = 1000;
    const int FAST_DROP = 1;

    // Size of a tetromino component
    const int STEP = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / STEP;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / STEP;

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind { HORIZONTAL,
        LEFT_CORNER,
        RIGHT_CORNER,
        SQUARE,
        STEP_UP_RIGHT,
        PYRAMID,
        STEP_UP_LEFT,
        NUMBER_OF_TETROMINOS };

    struct Tetro_ {

        QColor colour;
        std::vector<int> y_offset;
        std::vector<int> x_offset;
    };

    // all different type of tetrominos
    std::vector<Tetro_> tetrominos_;

    // all colours for tetrominos
    const std::vector<QColor> colours_ = {
        Qt::cyan,
        Qt::blue,
        Qt::darkGray,
        Qt::yellow,
        Qt::green,
        Qt::magenta,
        Qt::red,
    };

    // x offset for each block on during building
    const std::vector<std::vector<int> > x_ = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, -3 },
        { 0, 0, 0, -1 },
        { 1, 0, 0, -1 },
        { 0, 0, -1, -1 },
        { 0, 0, 0, -2 },
        { 0, 0, 0, -2 },
    };

    // y offset for each block during building
    const std::vector<std::vector<int> > y_ = {
        { -1, -1, -1, -1 },
        { 0, 0, 0, -1 },
        { 0, 0, 0, -1 },
        { -1, 0, 0, -1 },
        { 0, 0, -1, -1 },
        { 0, 0, 0, -1 },
        { -1, 0, 0, -1 },
    };

    // different rotational positions
    enum rotations_ { UP,
        LEFT,
        DOWN,
        RIGHT };

    /**
     * @brief keyPressEvent
     * @param event, key what was pressed
     * when a key is pressed, checks if that key was either "w,a,s,d"
     * and calls correct methods accordingly. ignores all other key presses.
     */
    void keyPressEvent(QKeyEvent* event);
    /**
     * @brief builder
     * Creates each tetromino block by block and moves them to the center
     * to be dropped. Resets rotational value.
     */
    void builder();
    /**
     * @brief isValid
     * @param block, pointer to block (RectItem) in question
     * @param horizontal, horizontal movement attempted
     * @param vertical, vertical movement attempted.
     * @return bool, true if valid movement, false otherwise.
     * Checks is a movement is valid for a specific block.
     */
    bool isValid(QGraphicsRectItem* block, int horizontal, int vertical);
    /**
     * @brief horizontalMovement
     * @param dir, direction where to move (LEFT/RIGHT)
     * Attempts to move all active blocks in a horizontal direction.
     * If it cannot, will not allow movement to be made.
     */
    void horizontalMovement(int dir);
    /**
     * @brief verticalMovement
     * Attempts to move all active blocks down. If it cannot,
     * calls either game ends or new active blocks are created.
     */
    void verticalMovement();
    /**
     * @brief anchorBlocks
     * if game has not ended, turns current active blocks into static ones
     * and calls for the creation of new active blocks and speeds up game
     */
    void anchorBlocks();
    /**
     * @brief rotate
     * @param num, what tetromino is currently active
     * rotates entire tetromino if possible, will not allow movement
     * if not.
     */
    void rotate(int& num);
    /**
     * @brief timeKeeping
     * keeps track of time in minutes and seconds.
     */
    void timeKeeping();
    /**
     * @brief scoreKeeping
     * keeps track of score and updates it if needed.
     */
    void scoreKeeping();
    /**
     * @brief isGameOver
     * Checks if creating new blocks collide with static blocks.
     * if so, game is declared as ended.
     */
    bool isGameOver();
    /**
     * @brief gameHasEnded
     * Re-enables buttons and gives confirmation to user that game has ended.
     * Also does endgame cleanup, like stopping timers.
     */
    void gameHasEnded();
    /**
     * @brief clearPrevious
     * Clears previous game by clearing game
     * board reseting score and timer speed.
     */
    void clearPrevious();

    int sec_ = 0;
    int min_ = 0;

    int speed_ = INITIAL_SPEED;
    int score_ = 0;

    // rotation of a block
    int rotation_;

    // what specific tetromino is currently active (-1 = NONE)
    int current_= -1;
};

#endif // MAINWINDOW_HH
