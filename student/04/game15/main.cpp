/* Game15 (or puzzle 15) : Template code
 *
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author:
 * Name: Aleksi Rissa
 * Student number: 292053
 * UserID: xfalri
 * E-Mail: aleksi.rissa@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include "board.hh"
#include <iostream>


// More functions
void init_board(Board game)
{
    game.print();

}

void read_integers(std::vector< unsigned int >& custom)
{
    int new_integer = 0;
    for(int i = 0; i < 16; ++i)
    {
        std::cin >> new_integer;
        custom.push_back(new_integer);
    }
}


int main()
{
    std::string ans;
    std::vector<unsigned int> custom;

    std::cout << "Random initialization (y/n): ";
    std::cin >> ans;

    if ( ans == "y"){
        std::cout << "ayy lmao" << std::endl;
        Board game = Board(true, custom);
    } else if ( ans == "n"){
        std::cout <<"Enter the numbers 1-16 in a desired order (16 means empty): " << std::endl;
        read_integers(custom);
        Board game = Board(false, custom);
        init_board(game);
    }


    return EXIT_SUCCESS;
}
