#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

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

map<string,vector<string>> dudes;
int max_depth = 0;
int size = 0;

void print_me_and_underlings(int depth, string me) {
    for (int i=0; i < depth; ++i){
        cout << "..";
    }
    depth++;
    cout << me << endl;
    for (string dude : dudes[me]) {
        print_me_and_underlings(depth, dude);
    }
}

void count_me_and_underlings(int depth, string me) {
    int my_depth = depth;
    my_depth++;
    for (string dude : dudes[me]) {
       count_me_and_underlings(my_depth, dude);
       if (my_depth > max_depth)
           max_depth = my_depth;
    }
    my_depth--;
}

void depth_me_and_underlings(string me) {
    size++;
    for (string dude : dudes[me])
       depth_me_and_underlings(dude);
}

int main()
{
    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            } else {

                string id1 = parts.at(1);
                string id2 = parts.at(2);

                if (dudes.find(id1) == dudes.end())
                    dudes[id1];
                dudes[id1].push_back(id2);
            }

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            print_me_and_underlings(0, id);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            size = -1;
            if (dudes.find(id) == dudes.end()){
                cout << "0" << endl;
            } else {
                depth_me_and_underlings(id);
                cout << size << endl;
            }



        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            max_depth = 1;
            count_me_and_underlings(1, id);
            cout << max_depth << endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
