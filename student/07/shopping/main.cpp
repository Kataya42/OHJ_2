/* Chain stores
 *
 * Desc:
 *
 * Program lets user input a CSV file. Program will interpret that
 * Information as listings of products with their store chain and location
 * Included. User then can using commands via the user interface.
 * Commands with their correct syntax are: "chain", "stores <chain_store>",
 * "selection <chain_store> <store_location>", "cheapest <product_name>" and
 * "products". User can search for information from given file
 * Using these commands or quit the program using "quit".
 *
 *
 * Program author:
 * Name: Aleksi Rissa
 * Student number: 292053
 * UserID: xfalri
 * E-Mail: aleksi.rissa@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * The chosen data structure for this program is a three layer map
 * With the store chain pairs being the highest layer, then store pairs
 * Or their locations and finaly the product pairs. second values of the
 * Product pairs are structs named Product which contain the product name
 * And price information. Due to the way the program is implemented, when
 * When searching for product name you could either choose to take the
 * product pairs key value or the name parameter of the Product struct
 * The "last" layer is a map and not a vector to make searching and
 * Input easier. User interface happens in the menu fuction while inputfile
 * Integrity checking happens in the main function. Each command is divided
 * Into its own function.
 * */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip>

const double OUT_OF_STOCK = -1.0;

struct Product {
    std::string name;
    double price;
};

// defining stores to make rest of the code alot more readable.
typedef std::map< std::string, std::map< std::string , Product >> stores;

/**
 * @brief Splits a string into parts into a vector
 * @param s, string to be split
 * @param delimeter, character to indicate where the split happens
 * @param ingnore_empty, boolean dictating are empty spaces ignored or not
 * @return result, vector containing split string in parts
 */
std::vector < std::string > split(const std::string & s,
    const char delimiter, bool ignore_empty = false) {

    std::vector < std::string > result;
    std::string tmp = s;

    while (tmp.find(delimiter) != std::string::npos) {

        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());

        if (not(ignore_empty and new_part.empty()))
            result.push_back(new_part);
    }

    if (not(ignore_empty and tmp.empty()))
        result.push_back(tmp);

    return result;
}

/**
 * @brief from a vector, adds given elements into chains datastructure
 * @param chains, the nested map containing all information about store chains
 * @param line, vector of string containing information to be added.
 */
void inputFile(std::map < std::string, stores > & chains,
    const std::vector < std::string > & line) {

    double price = OUT_OF_STOCK;

    if (line[3] != "out-of-stock")
        price = stod(line[3]);

    Product prod = {
        line[2],
        price
    };

    chains[line[0]][line[1]].insert({
        line[2],
        prod
    });
}

/**
 * @brief Checks does the given vector has as many elements as its supposed to
 * @param args, vector with all given arguments
 * @param correctNumber, unsigned int (1-3)
 * @return boolean whether amount of arguments was correct for given command
 */
bool correctArgs(const std::vector < std::string > & args,
    const unsigned int & correctNumber) {

    if (args.size() == correctNumber) {
        return true;
    } else {
        std::cout << "Error: error in command " << args[0] << std::endl;
        return false;
    }
}

/**
 * @brief Prints all items in highest layer of chains (store chain names)
 * @param chains, the nested map containing all information about store chains
 */
void findChains(const std::map < std::string, stores > & chains) {

    for (std::pair < std::string,
         stores > chainPair: chains) {

        std::cout << chainPair.first << std::endl;
    }
}

/**
 * @brief Prints all stores (or their locations) from given store chain
 * @param chains, the nested map containing all information about store chains
 * @param chain, string with the name of the chain
 */
void findStores(std::map < std::string, stores > & chains,
    const std::string & chain) {

    if (chains.find(chain) == chains.end()) {
        std::cout << "Error: unknown chain name" << std::endl;
    } else {
        for (std::pair < std::string,
             std::map < std::string, Product >> storePair: chains[chain]){

            std::cout << storePair.first << std::endl;
        }
    }
}

/**
 * @brief Prints the entire selection of given store from given chain
 * @param chains, the nested map containing all information about store chains
 * @param chain, string with the name of the chain
 * @param store, string with the name of the store
 */
void findSelection(std::map < std::string, stores > & chains,
    const std::string & chain,
        const std::string & store) {


    if (chains.find(chain) == chains.end()) {
        std::cout << "Error: unknown chain name" << std::endl;

    } else if (chains[chain].find(store) == chains[chain].end()) {
        std::cout << "Error: unknown store" << std::endl;

    } else {
        // for each product pair in given store
        for (std::pair < std::string,
             Product > productPair: chains[chain][store]) {

            if (productPair.second.price == OUT_OF_STOCK) {
                std::cout << productPair.second.name <<
                             " out of stock" << std::endl;

            } else {
                std::cout << productPair.second.name <<
                             " " << productPair.second.price << std::endl;
            }
        }
    }
}

/**
 * @brief Finds out what is the cheapest price given product has, if any, then
 *        prints that price, and all stores with that price on that product
 * @param chains, the nested map containing all information about store chains
 * @param product, string with the name of the product
 */
void findCheapest(const std::map < std::string, stores > & chains,
    const std::string & product) {

    double cheapestPrice = __DBL_MAX__;
    bool isNotInStock = false;

    // finding the cheapest price for given product
    for (std::pair < std::string,
         stores > chainPair: chains) {
        for (std::pair < std::string,
             std::map < std::string, Product >> storePair: chainPair.second) {

            // Checks whether product exists and
            // is it cheaper than previous entries
            if (storePair.second[product].price > 0 &&
                    storePair.second[product].price < cheapestPrice) {
                cheapestPrice = storePair.second[product].price;

            } else if (storePair.second[product].price == OUT_OF_STOCK) {
                isNotInStock = true;
            }
        }
    }

    if (cheapestPrice == __DBL_MAX__ && isNotInStock) {
        std::cout << "The product is temporarily "
                     "out of stock everywhere" << std::endl;

    } else if (cheapestPrice == __DBL_MAX__) {
        std::cout << "The product is not "
                     "part of product selection" << std::endl;

    } else {
        std::cout << std::fixed << std::setprecision(2)
                  << cheapestPrice << " euros" << std::endl;

        // Once the cheapest price is found, we then find all stores
        // with that price for given product
        for (std::pair < std::string,
             stores > chainPair: chains) {
            for (std::pair < std::string,
                 std::map < std::string, Product >> storePair: chainPair.second) {

                if (storePair.second[product].price == cheapestPrice) {
                    std::cout << chainPair.first <<
                                 " " << storePair.first << std::endl;
                }
            }
        }
    }
}

/**
 * @brief Prints all products listed in all store chains ingoring dupicates
 * @param chains, the nested map containing all information about store chains
 */
void findProducts(const std::map < std::string, stores > & chains) {

    std::vector < std::string > foundItems;

    // search for each product listed
    for (std::pair < std::string,
         stores > chainPair: chains) {
        for (std::pair < std::string,
             std::map < std::string, Product >> storePair: chainPair.second) {
            for (std::pair < std::string,
                 Product > productPair: storePair.second) {

                // if it has not been printed already
                if (not(std::find(foundItems.begin(), foundItems.end(),
                            productPair.second.name) != foundItems.end())) {

                    foundItems.push_back(productPair.second.name);
                    std::cout << productPair.second.name << std::endl;
                }
            }
        }
    }
}

/**
 * @brief UI happens from this function, calls other fucntions depending
 *        on what command is written.
 * @param chains, the nested map containing all information about store chains
 */
void menu(std::map < std::string, stores > & chains) {

    std::string input;

    while (input != "quit") {

        std::cout << "> ";
        getline(std::cin, input);
        std::vector < std::string > args = split(input, ' ', true);

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

        } else if (args[0] != "quit") {
            if (correctArgs(args, 1))
                std::cout << "Error: "
                             "unknown command: " << args[0] << std::endl;
        }
    }
}

int main() {

    std::string input;
    // Initialization said datastructure
    std::map < std::string,
            std::map < std::string,
            std::map < std::string, Product >> > chains;

    std::cout << "Input file: ";
    getline(std::cin, input);

    std::ifstream file_object(input);

    if (not file_object) {
        std::cout << "Error! The file cannot be opened." << std::endl;
        return EXIT_FAILURE;

    } else {
        std::string line;

        while (getline(file_object, line)) {
            std::vector < std::string > strings = split(line, ';', true);

            if (strings.size() != 4) {
                std::cout << "Error: the input file "
                             "has an erroneous line" << std::endl;
                return EXIT_FAILURE;

            } else {
                inputFile(chains, strings);
            }
        }
        menu(chains);
    }
    return EXIT_SUCCESS;
}
