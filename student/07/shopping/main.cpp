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
#include <algorithm>

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

    double price = 98;
    if ( line[3] != "out-of-stock")
        price = stod(line[3]);

    Product pro;
    pro.name = line[2];
    pro.price = price;

    //all.insert({line[0],{}});
    //all[line[0]].insert({line[1],{}});
    all[line[0]][line[1]].insert({line[2],pro});
}
bool correctArgs(const std::vector<std::string> &args, const unsigned int &correctNumber){
    if (args.size() == correctNumber){
        return true;
    } else {
        std::cout << "Error: error in command " << args[0] << std::endl;
        return false;
    }

}
void Findcheapest(const std::map< std::string,std::map < std::string, std::map <std::string, Product>> > &all,const std::vector<std::string> &args){
    //std::cout << "cheapest products of selected name" << std::endl;
    double cheapestPrice = 99;
    for (auto c : all){
        for (auto v : c.second){
            if (v.second[args[1]].price > 0 && v.second[args[1]].price < cheapestPrice){
                cheapestPrice = v.second[args[1]].price;

            }
        }
    }

    if (cheapestPrice == 99) {
        std::cout << "The product is not part of product selection" << std::endl;
    } else if (cheapestPrice == 98){
        std::cout << "The product is temporarily out of stock everywhere" << std::endl;
    }else {
        std::cout << cheapestPrice << " euros" << std::endl;

        for (auto c : all){
            for (auto v : c.second){
                if (v.second[args[1]].price == cheapestPrice){
                    std::cout << c.first << " " << v.first << std::endl;
                }
            }
        }
    }
}
void findProducts(const std::map< std::string,std::map < std::string, std::map <std::string, Product>> > &all){
    //std::cout << "here are all prodcuts there are" << std::endl;
    std::vector<std::string> foundItems;
    for (auto c : all){
        for (auto v : c.second){
            for (auto b : v.second){
                if (std::find(foundItems.begin(), foundItems.end(), b.second.name) != foundItems.end())
                {

                } else {
                    foundItems.push_back(b.second.name);
                    std::cout << b.second.name << std::endl;
                }

            }
        }

    }

}
void menu( std::map< std::string,std::map < std::string, std::map <std::string, Product>> > &all) {

    std::string input;
    while (input != "quit") {
        std::cout << "> ";
        getline(std::cin, input);
        std::vector<std::string> args = split(input, ' ', true);

        if (args[0] == "chains") {
            if (correctArgs(args, 1)){
                for (auto c : all)
                    std::cout << c.first << std::endl;
            }
        } else if (args[0] == "stores") {

             if (correctArgs(args, 2)) {
                 if ( all.find(args[1]) == all.end() ) {
                   std::cout << "Error: unknown chain name" << std::endl;
                 } else {
                     for (auto c : all[args[1]])
                         std::cout << c.first << std::endl;
                 }
            }
        } else if (args[0] == "selection") {
             if (correctArgs(args, 3)) {
                 if ( all.find(args[1]) == all.end() ) {
                   std::cout << "Error: unknown chain name" << std::endl;
                 } else if (all[args[1]].find(args[2]) == all[args[1]].end()){
                   std::cout << "Error: unknown store" << std::endl;
                 } else {
                    for (auto c : all[args[1]][args[2]])
                        std::cout << c.second.name << " " << c.second.price <<std::endl;
                 }
             }
        } else if (args[0] == "cheapest") {
             if (correctArgs(args, 2))
                Findcheapest(all, args);

        } else if (args[0] == "products") {
            if (correctArgs(args, 1))
                findProducts(all);

        }  else if (args[0] != "quit") {
             if (correctArgs(args, 1))
                std::cout << "Error: unknown command: " << args[0] << std::endl;
        }
    }
}
int main() {
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

    return EXIT_SUCCESS;
}
