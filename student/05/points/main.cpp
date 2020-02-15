#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    map<string,int> scores;
    string input = "a.input";
    cout << "Input file: ";
    getline(cin, input);

    ifstream file_object(input);
    if (not file_object) {
        cout << "Error! The file " << input <<  " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {

        string stuf;


        while (getline(file_object, stuf)){
            bool sep = false;
            string score;
            string person;

                for (char c : stuf){
                    if (c == ':'){
                        sep = true;
                    } else if(sep == true){
                        score += c;
                    } else {
                        person +=c;

                    }
                }
            int numbers = stoi(score);
            if ( scores.find(person) != scores.end() ) {
                // The word was found in the map.
                scores[person] = scores[person]+ numbers;
            } else {
                // The word was not found in the map.
                scores[person] = numbers;
            }


        }
        cout << "Final scores:" << endl;
        for (auto i : scores){
            cout << i.first << ": ";
            cout << i.second << endl;
        }

    }

    return EXIT_SUCCESS;
}
