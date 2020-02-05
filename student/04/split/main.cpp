#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string line, char sep, bool a =false){

    if (a == false){
        string temp = "";
        vector<string> result;

        for (char i : line){
            result.push_back(""+i);
        }
        return result;
    } else {
        string temp2 = "";
        vector<string> result;
        result.push_back(""+sep);
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
