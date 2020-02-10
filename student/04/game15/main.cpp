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
 * Program creates a Board object using a boolean and a vector of ints, this
 * can bec onsidered the game board. There are no user inputs inside the
 * object aside from seed creation, if necesary. A turn of the game happens
 * in a while loop inside the gameplay fucntion.
 * It contains all phases to ensure a sucssesful and legal turn.
 * Program also checks weather created board can
 * be solved, informs the user about it and ends the program if not so.
 * Game is scalable by changing the value of SIZE, LENGTH and EMPTY
 *
 * */

#include "board.hh"
#include <iostream>
#include <string>
#include <algorithm>
// the amount of numbers to be added to the grid
// must be equal to MAX for program to work
// (SIZE * SIZE, default 16)
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
    std::cin.ignore();

 }

/**
 * @brief Checks the given vector does it contain all necesary numbers
 * @param init_vector, the vector to be checked
 * @return boolean whether vector was correct or not
 */
bool isCorrect(std::vector< unsigned int >& init_vector) {

    // vector to store all missing integers
    std::vector<int> missing_ints;

    // checks original vector for integers and if not found
    // adds them to missing integers vector
    for (int i = 1; i < LENGTH; ++i) {
        if (not (std::count(init_vector.begin(), init_vector.end(), i))) {
            missing_ints.push_back(i);
        }
    }

    // if there is a missing integer, prints it and returns true
    // only prints the first missing integer
    if (missing_ints.size()!= 0) {
        std::cout << "Number " << (missing_ints[0])
                << " is missing" << std::endl;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Fuction asks the user for a command (direction) and a number
 * @return input, entire string of inputs the user has submitted
 */
std::string userInput() {

    // reseting all strings inbetween command inputs
    std::string buffer = "";
    std::string input = "";
    int temp  = 0;

    // takes two strings from user
    std::cout << "Dir (command, number): ";
    while (temp < 2 && buffer != "q") {
        std::cin >> buffer;
        input += buffer;
        input += " ";
        temp ++;

    // clearing the cin buffer
    std::cin.ignore();

    }
    return input;
}

/**
 * @brief Fuction checks are the given user inputs valid
 *        and if so, attempts to move them
 * @param game, object containing all information concerning the game state
 * @param direction_string, string with the user inputted direction to move
 * @param number_string, string with the user inputted number to move
 */
void PieceMovement(Board& game, std::string direction_string,
                   std::string number_string) {

    // Checks if the second string contains only numbers
    bool is_digits = true;
    for (char c : number_string){
        if (not (c >= '0' && c <= '9')) {
            is_digits = false;
        }
    }

    // if input is not any of the allowed dirctions, prints unknown command
    if (not (direction_string == "w" || direction_string == "a"
             || direction_string == "s" || direction_string == "d")) {
        std::cout << "Unknown command: " << direction_string << std::endl;

    // else if it is not any of the allow numbers in range
    // or not an number at all prints Invalid number
    } else if (is_digits == false || std::stoi(number_string) < 0
               || std::stoi(number_string) > LENGTH-1 ) {
        std::cout << "Invalid number: " << number_string << std::endl;

    // else if all checks out, attempts to do the requested Movement
    } else {
       char direction = direction_string[0];
       int number = std::stoi(number_string);
       game.action(direction, number);
    }
    // finally updates the game board
    game.print();
}

/**
 * @brief Handles gameplay after the board has been properly initialized
 * @param game, object containing all information concerning the game state
 */
void gameplay(Board& game) {

    bool has_quit = false;

    // while the game has not achived victory
    // and user has not inputted "q" or quit.
    while(not game.isVictory() && not has_quit) {
        bool space_pressed = false;
        std::string number_string  = "";
        std::string direction_string = "";

        // get the user inputted string
        std::string input = userInput();

        // dividing the input into two strings,
        // one for direction command, the other for the number
        for (char c : input) {
            if (c == ' ') {
                // separated by space
                space_pressed = true;
            } else if (not space_pressed) {
                direction_string += c;
            } else {
                number_string += c;
            }
        }

        // if user has not quit, proceeds to move a
        // piece with given direction and number
        if(direction_string != "q") {
            PieceMovement(game, direction_string, number_string);
        } else {
            has_quit = true;
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
            // length of the amount of digits user is requested depends
            // on what sized board is desired
            std::cout <<"Enter the numbers 1-"<< LENGTH <<
                        " in a desired order (" << LENGTH <<
                        " means empty):" << std::endl;
            customVector(init_state);
            if (isCorrect(init_state)) {
                 return EXIT_FAILURE;
            }

        // else if creates a vector with numbers in order
        } else if (ans == "y") {
            for(int i = 1; i < LENGTH + 1; i++) {
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
