#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int main()
{
    map<string,vector<int>> occurance;
    string input = "";
    cout << "Input file: ";
    getline(cin, input);

    ifstream file_object(input);
    if (not file_object) {
        cout << "Error! The file " << input <<  " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
       string stuf;

       int line = 1;
       char sep = ' ';

        while (getline(file_object, stuf)){

            string temp;
            for (char c : stuf){
                vector<int> rows;
                if (c == sep){
                    if (occurance.find(temp) != occurance.end()) {
                        // found
                        occurance[temp].push_back(line);
                    } else {
                        // not found, make new
                        rows.push_back(line);
                        occurance[temp] = rows;
                    }
                    temp = "";
                } else {
                    temp += c;
                }
            }

            if (occurance.find(temp) != occurance.end()) {
                // found
                occurance[temp].push_back(line);
            } else {
                // not found, make new
                vector<int> rows;
                rows.push_back(line);
                occurance[temp] = rows;
            }

            line ++;
        }

       for (auto c : occurance){
           string locations;
            for (unsigned int i=0; i<c.second.size(); i++){
               locations += to_string(c.second[i]);
               if (i == c.second.size()-1){

               } else {
                   locations += ", ";
               }


           }
           cout << c.first << " " << c.second.size() << ": " << locations << endl;
       }
       }

    return EXIT_SUCCESS;
}
