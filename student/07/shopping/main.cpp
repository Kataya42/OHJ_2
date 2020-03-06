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


    std::string store = line[0];
    std::string location = line[1];
    std::string product = line[2];
    double price = 0;

    if ( line[3] != "out-of-stock")
        price = stod(line[3]);

    Product pro;
    pro.name = product;
    pro.price = price;

    all.insert({store,{}});
    all[store].insert({location,{}});
    all[store][location].insert({product,pro});



   // if (price == 0){
   //     std::cout << store << " " << location << " " << product << " out of stock" << std::endl;
   // } else {
   //     std::cout << store << " " << location << " " << product << " " << price << std::endl;
   //  }




}

int main()
{
    std::string input = "products.input";

    std::map< std::string,std::map < std::string, std::map <std::string, Product>> > all;

    // map with store name ( map with location name ( map with products)))
    // store chain
        // store location
            // product
                // name
                // price

    // std::vector<std::string> all_the_stuff;

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
    // for (unsigned int i = 0; i < all.size(); i++){
    //    std::cout  << i << std::endl;
    // }
    std::cout << all["Prisma"]["Lielahti"]["sausage"].name << " " << all["Prisma"]["Lielahti"]["sausage"].price << std::endl;

    return EXIT_SUCCESS;
}
