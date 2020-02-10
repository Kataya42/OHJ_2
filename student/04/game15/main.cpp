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

const int LENGTH = 16;

/**
 * @brief Function for adding numbers in an desired order in a vector
 * @param init_vector, the vector to be filled with custom numbers
 */
void customVector(std::vector< unsigned int >& init_vector) {

    int new_integer = 0;

    // Creation of vector with user inputed integers in order
    for(int i = 0; i < LENGTH; ++i) {
        std::cin >> new_integer;
        init_vector.push_back(new_integer);
    }

    // clearing the cin buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

 }

/**
 * @brief Checks the given vector does it contain all necesary numbers
 * @param init_vector, the vector to be checked
 * @return boolean whether vector was correct or not
 */
bool isCorrect(std::vector< unsigned int >& init_vector){

    // vector to store all missing integers
    std::vector<int> missing_ints;

    // checks original vector for integers and if not found
    // adds them to missing integers vector
    for (int i = 1; i < LENGTH; ++i) {
        if (not (std::count(init_vector.begin(), init_vector.end(), i))){
            missing_ints.push_back(i);
        }
    }

    // if there is a missing integer, prints it and returns true
    if (missing_ints.size()!= 0) {
        std::cout << "Number " << (missing_ints[0])
                << " is missing" << std::endl;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Handles gameplay after the board has been properly initialized
 * @param game, object containing all information concerning the game state
 */
void gameplay(Board game) {

    // for checking does user want to quit the game
    bool has_quit = false;
    // the direction user wants to move
    char direction;
    // the number to be moved
    int number;

    // while the game has not achived victory and user has not inputted "q" or quit.
    while(not (game.isVictory() || has_quit)) {
        std::cout << "Dir (command, number): ";
        for (int i = 0; i < 2; i++) {
            // checks the first character of the string
            if (i == 0){
                std::cin >> direction;
                // breaks the loop if input is "q" or quit
                if (direction == 'q') {
                    has_quit = true;
                    break;
                }
            } else {
                std::cin >> number;
            }
        }

        if(not has_quit) {
            // clearing the cin buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // if input is not any of the allowed dirctions, throws an error
            if (not (direction == 'w' || direction == 'a'
                     || direction == 's' || direction == 'd')) {
                std::cout << "Unknown command: " << direction << std::endl;

            // else if it is not any of the allow numbers in range, throws an error
            } else if (number < 0 || number > LENGTH-1) {
                std::cout << "invalid number: " << number << std::endl;

            // else if all checks out, attempts to do the requested action, or movement
            } else {
               game.action(direction, number);
            }
            // finally updates the game board
            game.print();
        }
    }
}

int main() {

    // vector for storing initial state of the game board
    std::vector<unsigned int> init_state;
    std::string ans;

    while (not (ans == "n" || ans == "y")) {
        std::cout << "Random initialization (y/n): ";
        std::getline(std::cin, ans);

        // If answer is n, will forward the user to custom inputs
        if (ans == "n") {
            std::cout <<"Enter the numbers 1-16 in a desired order"
                        " (16 means empty):" << std::endl;
            customVector(init_state);
            if (isCorrect(init_state)) {
                 return EXIT_FAILURE;
            }

        // else if creates a vector with numbers in order
        } else if (ans == "y") {
            for(int i = 1; i < LENGTH + 1; i++){
                init_state.push_back(i);
            }

        // else propts user answer again
        } else {
            std::cout << "Unknown choice: " << ans << std::endl;
        }
    }

    Board game = Board((ans=="y"), init_state);

    // if game is solvable, prints the board and starts the gameplay
    if (game.isSolvable()) {
        game.print();
        gameplay(game);
    }
    return EXIT_SUCCESS;
}
