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

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;

Board::Board(bool shuffle, std::vector<unsigned int> inputs):
    shuffle_(shuffle){
    if (not shuffle){
        normal_init(inputs);
    } //(else {
      //  my_shuffle();
      //}
}

void Board::normal_init(std::vector<unsigned int> input)
{
    int temp = 0;

    for (int i = 0; i < 4; i++) {
        std::vector<unsigned int> row;
        for (int j = 0; j < 4; j++) {
            unsigned count = input.at(temp);
            row.push_back(count);
            temp += 1;
        }
        grid_.push_back(row);

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
}

