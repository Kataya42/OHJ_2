#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int main()
{
    map<string,int> occurance;
    string input = "hell.txt";
    vector<string> words;
    vector<string> lines;
    vector<string> locations;
    //cout << "Input file: ";
    //getline(cin, input);

    ifstream file_object(input);
    if (not file_object) {
        cout << "Error! The file " << input <<  " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
       string stuf;

       int line_by = 1;
       char sep = ' ';

        while (getline(file_object, stuf)){
            string temp;
            for (char c : stuf){
                if (c == sep){
                    words.push_back(temp);
                    temp = "";
                } else {
                    temp += c;
                }
            }
            words.push_back(temp);
            string test = to_string(line_by);
            stuf += test;
            lines.push_back(stuf);
            line_by ++;

        }
        for (auto i : words){
            if ( occurance.find(i) != occurance.end() ) {
                // The word was found in the map.
                occurance[i] = occurance[i]+1;
            } else {
                // The word was not found in the map.
                occurance[i] = 1;
            }

//        }
//        for (auto c: occurance){
//            if (find(lines.begin(), lines.end(), c.first) != lines.end()){
//                cout << "yes" << endl;
//            } else {
//                cout << "no" << endl;
//            }

        }
        for (auto c : lines){
            cout << c << endl;
        }
        for (auto c : occurance){
            cout << c.first << " " << c.second << ":" << endl;
        }
    }

    return EXIT_SUCCESS;
}
