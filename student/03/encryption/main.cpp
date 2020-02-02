#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


int main()
{
    string text;
    string key;
    //string text = "quickbrownfoxjumpsoverthelazydog";
    string def = "abcdefghijklmnopqrstuvwzyx";
    //key = "qwertyuiopasdfghjklzxcvbnm";
    cout << "Enter the encryption key: ";
    cin >> key;

    if (key.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
        }

    for( char& i : key){
        if (isupper(i)){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
      }
    }


    for( char letter = 'a'; letter < 'z'; ++letter ){
        string::size_type test = key.find(letter);
        if (test == string::npos){
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return EXIT_FAILURE;
            }

    }
   cout << "Enter the text to be encrypted: ";
    cin >> text;

    char buffer[text.length()+1];

    for(uint i=0; i < text.length(); i++){
        int index = (int)text[i];
        buffer[i] = key[index-97];

//                key[key.find(text[i])];
//        string::size_type found = def.find(i);
//        string::size_type enc_found = key.find(i);
//        cout << found << "  " << enc_found <<endl;
//        buffer[found] = key[enc_found];
    }
    buffer[text.length()] = '\0';

    cout << "Encrypted text: " << buffer << endl;

//    cout << "Encrypted text: " <<key << " " << text << endl;
    return EXIT_SUCCESS;
}
