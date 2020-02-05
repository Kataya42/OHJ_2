#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string line, char sep, bool a =false){

    if (a == false){
        std::string temp = "";
        std::vector<std::string> result;

        for (char& c : line){

            if (c == sep){
                result.push_back(temp);
                temp = "";
            } else {
                temp += c;
            }

        }
        result.push_back(temp);
        return result;
    } else {
        std::string temp = "";
        std::vector<std::string> result;
        char test = 0;
        for (char& c : line){

            if (c == sep and test != sep){
                result.push_back(temp);
                temp = "";
            } else if (c == sep){

            } else {
                temp += c;
            }
            test = c;

        }
        result.push_back(temp);
        return result;
        }
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
