/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *  Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author:
 * Name: Aleksi Rissa
 * Student number: 292053
 * UserID: xfalri
 * E-Mail: aleksi.rissa@tuni.fi
 *
 * Notes:
 * Constructor takes two inputs, A boolean and an vector containing integers.
 * It will either shuffle (true) the integers, or not.(false)
 * By changing SIZE you can scale the board, but you also will have to
 * change EMPTY and LENGTH.
 * */

#ifndef BOARD_HH
#define BOARD_HH

#include <vector>

// size of one row
const int SIZE = 4;
// number of total slots in the entire grid
const unsigned int MAX = SIZE*SIZE;

class Board {
public:

    /**
     * @brief Constructor, Initializes a new instance of the Board class
     * @param shuffle boolean checks is given vector to be shuffled
     * @param numbers, integer vector to be used for creation of the grid
     */
    Board(bool shuffle, std::vector<unsigned int> numbers);

    /**
     * @brief Function prints the current game board state.
     */
    void print();

    /**
     * @brief Checks once whether game is solvable
     * @return true if game is solvavle
     */
    bool isSolvable();

    /**
     * @brief Checks if victory is achieved
     * @return returns true if victory has been achieved
     */
    bool isVictory();

    /**
     * @brief method for the moving of the board pieces
     * @param direction, Char showing the desired direction of the movement
     * @param number, integer showing the desired number to be moved
     */
    void action(char direction, unsigned int number);

private:
    /**
     * @brief Shuffles the numbers vector by using seed as a seed value
     * @param numbers, integer vector to be shuffled
     * @param seed, seed value to be used in the random generation
     */
    void myShuffle(std::vector<unsigned int>& numbers, int seed);

    /**
     * @brief creates the game grid
     * @param numbers integer vector that will be turned into the grid
     */
    void createGrid(std::vector<unsigned int> numbers);
    /**
     * @brief Creates seed for the randomizer
     * @return The created seed value, either inputted
     *         or taken from computer time.
     */
    int getSeed();

    //Game grid for the 15 puzzle
    std::vector<std::vector<unsigned int>> grid_;

};

#endif // BOARD_HH
