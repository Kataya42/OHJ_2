/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *
 * Program author:
 * Name: Aleksi Rissa
 * Student number: 292053
 * UserID: xfalri
 * E-Mail: aleksi.rissa@tuni.fi
 *
 * Notes:
 *
 * */

#include "board.hh"
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <string>

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;

Board::Board(bool shuffle, std::vector<unsigned int> numbers):
    shuffle_(shuffle){
    if (shuffle){
        // int seed = get_seed();
        my_shuffle(numbers, 3);
    } else {
        initialize(numbers);
      }
}

void Board::initialize(std::vector<unsigned int> numbers)
{
    int temp = 0;

    for (int i = 0; i < 4; i++) {
        std::vector<unsigned int> row;
        for (int j = 0; j < 4; j++) {
            unsigned count = numbers.at(temp);
            row.push_back(count);
            temp += 1;
        }
        grid_.push_back(row);

    }
}

int Board::get_seed()
{
    std::string seed = "";
    std::cout << "Enter a seed value or an empty line: ";
    std::getline(std::cin, seed);
    std::cout << seed;
    if (seed == ""){
        return time(NULL);
    } else {
        return stoi(seed);
    }
}
void Board::print()
{
    for(unsigned int x = 0; x < SIZE; ++x)
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY)
            {
                std::cout << grid_.at(x).at(y);
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void Board::my_custom(std::vector<unsigned int>)
{

}

void Board::my_shuffle(std::vector<unsigned int> &numbers, int seed)
{
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
    initialize(numbers);


}

