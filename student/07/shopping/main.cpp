/* Chain stores
 *
 * Desc:
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
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

struct Product {
    std::string product_name;
    double price;
};

int main()
{
    std::string input = "products.input";


    std::vector<std::string> all_the_stuff;

    //std::cout << "Input file: ";
    //getline(cin, input);

    std::ifstream file_object(input);

    if (not file_object) {
        std::cout << "Error! The file cannot be opened." << std::endl;
        return EXIT_FAILURE;
    } else {
        std::string line;
        while (getline(file_object, line)){
            std::vector<std::string> strings = split(line, ';', true);
            all_the_stuff.push_back(strings[0]);
            all_the_stuff.push_back(strings[1]);
            all_the_stuff.push_back(strings[2]);
            all_the_stuff.push_back(strings[3]);
        }
    }

    int n = 1;
    for (auto i : all_the_stuff) {
        if (n % 4 == 0) {
            std::cout << i << std::endl;
            n++;
        }else {
            std::cout << i << " ";
            n++;
        }
    }
    return EXIT_SUCCESS;
}
