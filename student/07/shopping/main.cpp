/* Chain stores
 *
 * Descripion:
 *
 * A Program that is used to manage a database containing
 * information about products in stores. Program will interpret that
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
 * Or their locations and finaly the product pairs. Second values of the
 * Product pairs are structs named Product which contain the product name
 * And price information. Due to the way the program is implemented, when
 * When searching for product name you could either choose to take the
 * product pairs key value or the name parameter of the Product struct
 * The "last" layer is a map and not a vector to make searching and
 * Input easier. User interface happens in the menu fuction while inputfile
 * Integrity checking happens in the main function. Each command is divided
 * Into its own function.
 * */

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

const double OUT_OF_STOCK = -1.0;
const int COMMAND = 0;
const int CHAIN = 0;
const int STORE = 1;
const int PRODUCT = 2;
const int PRICE = 3;

/**
 * @brief The Product struct
 */
struct Product {
    std::string name;
    double price;
};

// defining stores to make rest of the code alot more readable.
typedef std::map < std::string, std::map < std::string, Product >> stores;

/**
 * @brief Splits a string into a vector of its parts
 * @param s, the string to be split
 * @param delimeter, a character to indicate where the split happens
 * @param ingnore_empty, a boolean value dictating whether
 *        empty spaces ignored or not
 * @return result, vector containing the split string
 */
std::vector < std::string > split(const std::string & s,
    const char delimiter, bool ignore_empty = false) {

    std::vector < std::string > result;
    std::string tmp = s;

    while (tmp.find(delimiter) != std::string::npos) {

        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());

        if (not(ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }

    if (not(ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }

    return result;
}

/**
 * @brief Checks does the given vector has as many elements as its supposed to
 * @param args, a vector with all given arguments
 * @param correctNumber, an unsigned int (1-3)
 * @return boolean whether amount of arguments was correct for given command
 */
bool correctArgs(const std::vector < std::string > & args,
    const unsigned int & correctNumber) {

    if (args.size() == correctNumber) {
        return true;
    } else {
        std::cout << "Error: error in command " << args[COMMAND] << std::endl;
        return false;
    }
}

/**
 * @brief Prints all chain names found in chains
 * @param chains, the nested map containing all information
 *        about the store chains and their products
 */

void findChains(const std::map < std::string, stores > & chains) {

    for (std::pair < std::string,
        stores > chainPair: chains) {
        std::cout << chainPair.first << std::endl;
    }
}

/**
 * @brief Prints all stores found in a given chain
 * @param chains, the nested map containing all information
 *        about the store chains and their products
 * @param chain, a string containing the name of the chain
 */
void findStores(std::map < std::string, stores > & chains,
    const std::string & chain) {

    // check if the given chain name is not in the database
    if (chains.find(chain) == chains.end()) {
        std::cout << "Error: unknown chain name" << std::endl;

    } else {
        // print each store that a given chain has
        for (std::pair < std::string,
            std::map < std::string, Product >> storePair: chains[chain]) {
            std::cout << storePair.first << std::endl;
        }
    }
}

/**
 * @brief Prints the entire selection of a given store from a given chain
 * @param chains, the nested map containing all information
 *        about the store chains and their products
 * @param chain, a string containing the name of the chain
 * @param store, a string containing the name of the store
 */
void findSelection(std::map < std::string, stores > & chains,
    const std::string & chain, const std::string & store) {

    // check if the given chain name is not in the database
    if (chains.find(chain) == chains.end()) {
        std::cout << "Error: unknown chain name" << std::endl;

    // or if given store name is not in the database
    } else if (chains[chain].find(store) == chains[chain].end()) {
        std::cout << "Error: unknown store" << std::endl;

    } else {
        // for each product pair in given store
        for (std::pair < std::string,
            Product > productPair: chains[chain][store]) {
            // print out of stock
            if (productPair.second.price == OUT_OF_STOCK) {
                std::cout << productPair.second.name <<
                    " out of stock" << std::endl;
            // print price
            } else {
                std::cout << productPair.second.name << " " <<
                    productPair.second.price << std::endl;
            }
        }
    }
}

/**
 * @brief Finds out what is the cheapest price a given product has, then
 *        prints that price, and all stores with that price on that product
 * @param chains, the nested map containing all information
 *        about the store chains and their products
 * @param product, a string containing the name of the product
 */
void findCheapest(const std::map < std::string, stores > & chains,
    const std::string & product) {

    double cheapestPrice = __DBL_MAX__;
    bool isFound = false;

    // finding the cheapest price for given product
    for (std::pair < std::string,
        stores > chainPair: chains) {
        for (std::pair < std::string,
            std::map < std::string, Product >> storePair: chainPair.second) {

            // Checks whether product exists and
            // whether is it cheaper than previously found cheapest entry
            if (storePair.second[product].price > 0 &&
                storePair.second[product].price < cheapestPrice) {
                cheapestPrice = storePair.second[product].price;

            // if the product exsists, but is out of stock
            } else if (storePair.second[product].price == OUT_OF_STOCK) {
                isFound = true;
            }
        }
    }

    // if product exists, but is out of stock in all strores
    if (cheapestPrice == __DBL_MAX__ && isFound) {
        std::cout << "The product is temporarily "
        "out of stock everywhere" << std::endl;

    // product does not exist in the database
    } else if (cheapestPrice == __DBL_MAX__) {
        std::cout << "The product is not "
        "part of product selection" << std::endl;

    // else product is in stock
    } else {
        std::cout << cheapestPrice << " euros" << std::endl;

        // Once the cheapest price is found, we then find all stores
        // with that price for given product
        for (std::pair < std::string,
            stores > chainPair: chains) {
            for (std::pair < std::string,
                std::map < std::string, Product >> storePair:
                chainPair.second) {

                // print all stores with the cheapest price
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
 * @param chains, the nested map containing all information
 *        about the store chains and their products
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
                }
            }
        }
    }
    // printing done separately so they will be always in correct order
    sort(foundItems.begin(), foundItems.end());
    for (std::string product: foundItems) {
        std::cout << product << std::endl;
    }
}

/**
 * @brief UI is implemented in this function, calls other fucntions depending
 *        on the entered command.
 * @param chains, the nested map containing all information
 *        about the store chains and their products
 */
void menu(std::map < std::string, stores > & chains) {
    std::string input;

    while (input != "quit") {

        std::cout << "> ";
        getline(std::cin, input);
        std::vector < std::string > args = split(input, ' ', true);

        if (args[COMMAND] == "chains") {
            if (correctArgs(args, 1)) {
                findChains(chains);
            }

        } else if (args[COMMAND] == "stores") {
            if (correctArgs(args, 2)) {
                findStores(chains, args[1]);
            }

        } else if (args[COMMAND] == "selection") {
            if (correctArgs(args, 3)) {
                findSelection(chains, args[1], args[2]);
            }

        } else if (args[COMMAND] == "cheapest") {
            if (correctArgs(args, 2)) {
                findCheapest(chains, args[1]);
            }

        } else if (args[COMMAND] == "products") {
            if (correctArgs(args, 1)) {
                findProducts(chains);
            }

        } else if (args[COMMAND] != "quit") {
            std::cout << "Error: "
            "unknown command: " << args[COMMAND] << std::endl;
        }
    }
}

/**
 * @brief Adds given elements into chains datastructure from a vector
 * @param chains, the nested map containing all information
 *        about the store chains and their products
 * @param line, a vector of string containing information to be added
 */
void inputFile(std::map < std::string, stores > & chains,
    const std::vector < std::string > & line) {

    double price = OUT_OF_STOCK;

    if (line[PRICE] != "out-of-stock") {
        price = stod(line[PRICE]);
    }

    // if the product is found
    if (chains[line[CHAIN]][line[STORE]].find(line[PRODUCT]) !=
        chains[line[CHAIN]][line[STORE]].end()) {
        // update its price
        chains[line[CHAIN]][line[STORE]][line[PRODUCT]].price = price;
    // else create a new product
    } else {
        Product prod = {
            line[PRODUCT],
            price};

        chains[line[CHAIN]][line[STORE]].insert({
            line[PRODUCT],
            prod});
    }
}

/**
 * @brief Function reads file into database if it can be processed succesfully
 * @param chains, the nested map containing all information
 *        about the store chains and their products
 * @param input, a string containing the name of the input file
 * @return true or false depending on whether the file reading was sucsessful
 */
bool readFile(std::map < std::string, stores > & chains, std::string & input) {

    std::ifstream file_object(input);

    if (not file_object) {
        std::cout << "Error: the input file cannot be opened" << std::endl;
        return false;

    } else {
        std::string line;

        while (getline(file_object, line)) {
            std::vector < std::string > strings = split(line, ';', true);

            if (strings.size() != 4) {
                std::cout << "Error: the input file "
                "has an erroneous line" << std::endl;
                return false;

            } else {
                inputFile(chains, strings);
            }
        }
    }
    return true;
}

int main() {

    std::string input;
    std::cout << "Input file: ";
    getline(std::cin, input);

    // declare the main data structure to use in the program
    std::map < std::string,
        std::map < std::string,
        std::map < std::string, Product >> > chains;

    // enter the main loop if file read was succesful
    if (readFile(chains, input)) {
        std::cout << std::fixed << std::setprecision(2);
        menu(chains);
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
