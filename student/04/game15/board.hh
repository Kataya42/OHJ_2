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
 * */

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>

const int SIZE = 4;

class Board {
public:

    // Constructor, Initializes a new instance of the Board class
    Board(bool shuffle, std::vector<unsigned int> inputs);  
    // Prints the game grid
    void print();
    // Checks once whether game is solvable, returns true if so
    bool is_solvable();
    // Checks if victory is achieved, returns true if so
    bool victory();
    // method for the moving of the board pieces
    void action(char dir, unsigned int num);

private:
    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(std::vector<unsigned int>& numbers, int seed);
    // Game grid for the 15 puzzle
    std::vector<std::vector<unsigned int>> grid_;
    // initializes the board
    void create_grid(std::vector<unsigned int>);
    // Creates seed for the randomizer
    int get_seed();

};

#endif // BOARD_HH
