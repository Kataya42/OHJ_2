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

    string input = "hell.txt";
    vector<string> words;
    vector<string> lines;
    //vector<string> locations;
    //cout << "Input file: ";
    //getline(cin, input);

    ifstream file_object(input);
    if (not file_object) {
        cout << "Error! The file " << input <<  " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
       string stuf;

       int line = 1;
       char sep = ' ';

        while (getline(file_object, stuf)){
            vector<int> rows;
            string temp;
            for (char c : stuf){
                if (c == sep){
                    // words.push_back(temp);
                    if (occurance.find(temp) != occurance.end()) {
                        // found
                        occurance[temp].push_back(line);
                    } else {
                        // not found, make new
                        rows.push_back(line);
                        occurance[temp] = rows;
                    }

                    //rows.push_back(line);
                    //occurance[temp] = rows;
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
                rows.push_back(line);
                occurance[temp] = rows;
            }
            //words.push_back(temp);
            // string test = to_string(line_by);
            // stuf += test;
            //lines.push_back(stuf);
            line ++;
        }

//        for (auto i : words){
//            if ( occurance.find(i) != occurance.end() ) {
//                // The word was found in the map.
//                occurance[i] = occurance[i]+1;
//            } else {
//                // The word was not found in the map.
//                occurance[i] = 1;
//            }

//        }

//        for (auto c: occurance){
//            if (find(words_s.begin(), words_s.end(), c.first) != words_s.end()){
//                cout << "yes" << endl;
//           } else {
//               cout << "no" << endl;
//            }

//        }




//        for (auto c : lines){
//            cout << c << endl;
//        }
       for (auto c : occurance){
           cout << c.first << " " << c.second.size() << ":" << endl;
       }
       }

    return EXIT_SUCCESS;
}
