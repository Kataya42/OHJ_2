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
#include <limits>

const double OUT_OF_STOCK = -1.0;
struct Product {
    std::string name;
    double price;
};

typedef std::map<std::string, std::map<std::string, Product>> stores;


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
void inputFile(std::map< std::string, stores > &chains, const std::vector<std::string> &line) {

    double price = OUT_OF_STOCK;
    if ( line[3] != "out-of-stock")
        price = stod(line[3]);

    Product prod = {line[2],price};
    chains[line[0]][line[1]].insert({line[2],prod});
}
bool correctArgs(const std::vector<std::string> &args, const unsigned int &correctNumber){
    if (args.size() == correctNumber){
        return true;
    } else {
        std::cout << "Error: error in command " << args[0] << std::endl;
        return false;
    }

}
void findChains(const std::map< std::string,stores  > &chains){
    for (std::pair <std::string,stores> chainPair : chains)
        std::cout << chainPair.first << std::endl;
}
void findStores(std::map< std::string, stores > &chains, const std::string &store){

    if ( chains.find(store) == chains.end() ) {
      std::cout << "Error: unknown chain name" << std::endl;
    } else {
        for (std::pair <std::string,std::map<std::string,Product>> storePair : chains[store])
            std::cout << storePair.first << std::endl;
    }
}
void findSelection(std::map< std::string, stores > &chains, const std::string &chain, const std::string &store){
    if ( chains.find(chain) == chains.end() ) {
      std::cout << "Error: unknown chain name" << std::endl;
    } else if (chains[chain].find(store) == chains[chain].end()){
      std::cout << "Error: unknown store" << std::endl;
    } else {
       for (std::pair <std::string,Product> productPair : chains[chain][store])
           std::cout << productPair.second.name << " " << productPair.second.price <<std::endl;
    }
}
void findCheapest(const std::map< std::string, stores > &chains, const std::string &product){
    double cheapestPrice = __DBL_MAX__;
    bool isNotInStock = false;
    for (std::pair <std::string,stores>  chainPair : chains){
        for (std::pair <std::string,std::map<std::string,Product>> storePair : chainPair.second){
            if (storePair.second[product].price > 0 && storePair.second[product].price < cheapestPrice){
                cheapestPrice = storePair.second[product].price;
            } else if (storePair.second[product].price == OUT_OF_STOCK){
                isNotInStock = true;
            }
        }
    }

    if (cheapestPrice == __DBL_MAX__ && isNotInStock) {
        std::cout << "The product is temporarily out of stock everywhere" << std::endl;
    } else if (cheapestPrice == __DBL_MAX__){
        std::cout << "The product is not part of product selection" << std::endl;
    }else {
        std::cout << cheapestPrice << " euros" << std::endl;

        for (std::pair <std::string,stores> chainPair : chains){
            for (std::pair <std::string,std::map<std::string,Product>> storePair : chainPair.second){
                if (storePair.second[product].price == cheapestPrice){
                    std::cout << chainPair.first << " " << storePair.first << std::endl;
                }
            }
        }
    }
}
void findProducts(const std::map< std::string, stores> &chains){
    //std::cout << "here are chains prodcuts there are" << std::endl;
    std::vector<std::string> foundItems;
    for (std::pair <std::string,stores> chainPair : chains){
        for (std::pair <std::string,std::map<std::string,Product>> storePair : chainPair.second){
            for (std::pair <std::string,Product> productPair : storePair.second){
                if (not (std::find(foundItems.begin(), foundItems.end(), productPair.second.name) != foundItems.end())){
                    foundItems.push_back(productPair.second.name);
                    std::cout << productPair.second.name << std::endl;
                }
            }
        }
    }
}
void menu(std::map< std::string,stores > &chains) {

    std::string input;
    while (input != "quit") {
        std::cout << "> ";
        getline(std::cin, input);
        std::vector<std::string> args = split(input, ' ', true);

        if (args[0] == "chains") {
            if (correctArgs(args, 1))
                findChains(chains);

        } else if (args[0] == "stores") {
             if (correctArgs(args, 2))
                findStores(chains, args[1]);

        } else if (args[0] == "selection") {
             if (correctArgs(args, 3))
                findSelection(chains, args[1], args[2]);

        } else if (args[0] == "cheapest") {
             if (correctArgs(args, 2))
                findCheapest(chains, args[1]);

        } else if (args[0] == "products") {
            if (correctArgs(args, 1))
                findProducts(chains);

        }  else if (args[0] != "quit") {
             if (correctArgs(args, 1))
                std::cout << "Error: unknown command: " << args[0] << std::endl;
        }
    }
}
int main() {
    std::string input = "products.input";

    std::map< std::string,std::map < std::string, std::map <std::string, Product>> > chains;

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
            inputFile(chains, strings);
        }
    }

    menu(chains);

    return EXIT_SUCCESS;
}
