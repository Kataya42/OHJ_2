#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

bool same_values(std::vector<int>vec){
    if (std::equal(vec.begin() + 1, vec.end(), vec.begin())){
        return true;
    } else {
        return false;
    }

}

bool is_ordered_non_strict_ascending(std::vector<int>vec){
    if (std::is_sorted(vec.begin(),vec.end())){
        return true;
    } else {
        return false;
    }

}

bool is_arithmetic_series(std::vector<int>vec){
    int test = vec.at(1) - vec.at(0);
    int truth = 0;
    for (unsigned long int i=0 ; i < vec.size(); i++){
        if (i != 0){
            if(vec.at(i) - vec.at(i-1) != test){
                truth = 1;
            }
        }
    }
    if(truth == 0){
        return true;
    } else {
        return false;
    }
}


bool is_geometric_series(std::vector<int>vec){
    for (int i : vec){
        if (i == 0){
            return false;
        }
    }
    int first = vec.at(0);
    int second = vec.at(1);
    float test = (float)first / (float)second;
    int truth = 0;
    for (unsigned long int i=0 ; i < vec.size(); i++){
        if (i != 0){
            if((float)vec.at(i-1) / (float)vec.at(i) != test){
                truth = 1;
            }
        }
    }
    if(truth == 0){
        return true;
    } else {
        return false;
    }
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
