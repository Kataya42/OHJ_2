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
#include <string>
#include <limits>
#include <algorithm>

// More functions
void init_board(Board game)
{
    game.is_solvable();
    game.print();
}

bool read_integers(std::vector< unsigned int >& custom)
{
    int new_integer = 0;
    std::vector<int> missing_ints;
    for(int i = 0; i < 16; ++i)
    {
        std::cin >> new_integer;
        custom.push_back(new_integer);
        }
    for (int i=1; i < 16; ++i){
        if (not (std::count(custom.begin(), custom.end(), i))){
            missing_ints.push_back(i);
      }
    }
    if (missing_ints.size()!= 0){
        std::cout << "Number " << (missing_ints[0]) << " is missing" << std::endl;
        return false;
    } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }


}

void gameplay(Board game)
{
    while( not game.victory()){
        char dir;
        int num;
        std::cout << "Dir (command, number): ";
        for (int i = 0; i < 2; i++){
            if (i == 0){
                std::cin >> dir;
             }   else {
                    std::cin >> num;
                }

        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (not (dir == 'w' || dir == 'a' || dir == 's' || dir == 'd')){
            std::cout << "Unknown command: " << dir << std::endl;
        } else if (num < 0 || num > 15){
            std::cout << "invalid number: " << num << std::endl;

        } else {
            game.action(dir, num);
        }


        game.print();
    }

}

int main()
{
    std::string ans;
    std::vector<unsigned int> init_state;

    while (not (ans == "n" or ans == "y") ){
        std::cout << "Random initialization (y/n): ";
        std::getline(std::cin, ans);

        if (ans == "n")  {
            std::cout <<"Enter the numbers 1-16 in a desired order (16 means empty): " << std::endl;
            if ( not (read_integers(init_state))){
                 return EXIT_FAILURE;
        }
        } else if ( ans == "y") {
            init_state= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        } else {
            std::cout << "Unknown choice: " << ans << std::endl;
        }
}
    Board game = Board((ans=="y"), init_state);
    init_board(game);
    gameplay(game);

    return EXIT_SUCCESS;
}
