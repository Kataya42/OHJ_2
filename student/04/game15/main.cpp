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
 *  Program creates a Board object using a boolean and a vector of ints, this
 * can bec onsidered the game board. There are no user inputs inside the
 * object aside from seed creation, if necesary. User inputs happen in the
 * "gameplay" fuction which calls all the necesary methods to
 * execute a turn in the game. Program also checks weather created board can
 * be solved, informs the user about it and ends the program if not so.
 *
 * */

#include "board.hh"
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

// Takes something :D:DD
bool read_integers(std::vector<unsigned int> &init_vector);
// TODO
void gameplay(Board game);

int main() {

    std::string ans;
    std::vector<unsigned int> init_state;

    while (not (ans == "n" || ans == "y") ) {
        std::cout << "Random initialization (y/n): ";
        std::getline(std::cin, ans);

        if (ans == "n") {
            std::cout <<"Enter the numbers 1-16 in a desired order"
                        " (16 means empty):" << std::endl;
            if ( not (read_integers(init_state))) {
                 return EXIT_FAILURE;
            }
        } else if ( ans == "y") {
            init_state= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        } else {
            std::cout << "Unknown choice: " << ans << std::endl;
        }
    }
    Board game = Board((ans=="y"), init_state);

    if (game.is_solvable()) {
        game.print();
        gameplay(game);
    }
    return EXIT_SUCCESS;
}

bool read_integers(std::vector< unsigned int >& init_vector) {

    int new_integer = 0;
    std::vector<int> missing_ints;

    for(int i = 0; i < 16; ++i) {
        std::cin >> new_integer;
        init_vector.push_back(new_integer);
    }
    for (int i = 1; i < 16; ++i) {
        if (not (std::count(init_vector.begin(), init_vector.end(), i))){
            missing_ints.push_back(i);
        }
    }
    if (missing_ints.size()!= 0) {
        std::cout << "Number " << (missing_ints[0])
                << " is missing" << std::endl;
        return false;
    } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }
}

void gameplay(Board game) {

    bool has_quit = false;
    char direction;
    int number;

    while( not (game.victory() || has_quit)) {
        std::cout << "Dir (command, number): ";
        for (int i = 0; i < 2; i++) {
            if (i == 0){
                std::cin >> direction;
                if (direction == 'q') {
                    has_quit = true;
                    break;
                }
            } else {
                std::cin >> number;
            }
        }

        if( not has_quit) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (not (direction == 'w' || direction == 'a'
                     || direction == 's' || direction == 'd')) {
                std::cout << "Unknown command: " << direction << std::endl;
            } else if (number < 0 || number > 15) {
                std::cout << "invalid number: " << number << std::endl;

            } else {
               game.action(direction, number);
            }
            game.print();
        }
    }
}
