#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    vector<string> lines;
    string input = "";
    string output = "";
    cout << "Input file: ";
    getline(cin, input);
    cout << "Output file: ";
   getline (cin, output);

    ifstream file_object(input);
    if (not file_object) {
        cout << "Error! The file " << input <<  " cannot be opened." << endl;
    } else {
        string stuf;
        while (getline(file_object, stuf)){
            lines.push_back(stuf);
        }
    }

    int num = 1;
    ofstream outfile(output);
    for (auto s : lines){
        outfile << num << " "<< s << endl;
        num++;
    }
    outfile.close();

    return 0;
}
