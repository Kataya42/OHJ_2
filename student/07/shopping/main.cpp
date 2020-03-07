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
    std::string name;
    double price;
};

void inputFile( std::map< std::string,std::map < std::string, std::map <std::string, Product>> > &all, const std::vector<std::string> &line) {

    double price = -1.0;
    if ( line[3] != "out-of-stock")
        price = stod(line[3]);

    Product pro;
    pro.name = line[2];
    pro.price = price;

    //all.insert({line[0],{}});
    //all[line[0]].insert({line[1],{}});
    all[line[0]][line[1]].insert({line[2],pro});
}

void menu(std::map< std::string,std::map < std::string, std::map <std::string, Product>> > &all) {

    std::string input;
    while (input != "quit"){
        std::cout << "> ";
        getline(std::cin, input);
        std::vector<std::string> args = split(input, ' ', true);

        if (args[0] == "chains"){
            std::cout << "here are the available store chains" << std::endl;
        } else if (args[0] == "stores") {
            std::cout << "here are the stores of a certain chain" << std::endl;
        } else if (args[0] == "selection") {
            std::cout << "here is the selection of a store" << std::endl;
        } else if (args[0] == "cheapest") {
            std::cout << "cheapest products of selected name" << std::endl;
        } else if (args[0] == "products") {
            std::cout << "here are all prodcuts there are" << std::endl;
        }  else if (args[0] != "quit") {
            std::cout << "Error: unknown command: " << args[0] << std::endl;
        }
    }
}

int main()
{
    std::string input = "products.input";

    std::map< std::string,std::map < std::string, std::map <std::string, Product>> > all;

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
            inputFile(all, strings);
        }
    }

    menu(all);
    // std::cout << all["Prisma"]["Lielahti"]["sausage"].name << " " << all["Prisma"]["Lielahti"]["sausage"].price << std::endl;

    return EXIT_SUCCESS;
}
