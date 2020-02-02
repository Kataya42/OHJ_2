#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


int main()
{

    string key;
    string text = "aapelix";
    string def = "abcdefghijklmnopqrstuvwzyx";
    key = "xbcdefghijklmnopqrstuvwzya";
    //cout << "Enter the encryption key: ";
    //cin >> key;

    if (key.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
        }

    for( char& i : key){
        if (isupper(i)){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
      }}


    for( char letter = 'a'; letter < 'z'; ++letter ){
        string::size_type test = key.find(letter);
        if (test == string::npos){
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return EXIT_FAILURE;
            }

    }
   //cout << "Enter the text to be encrypted: ";
   // cin >> text;

    for( char& i : text ){
        string::size_type found = def.find(i);
        cout << found << endl;

        //text.replace(found, found + 1, "x");
    }


    cout << "Encrypted text: " <<key << " " << text << endl;
    return EXIT_SUCCESS;
}
