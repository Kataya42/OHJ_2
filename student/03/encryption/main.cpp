#include <iostream>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;

int main()
{

    string key;
    string text;

    cout << "Enter the encryption key: ";
    cin >> key;

    if (key.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        }
    cout << endl;
    for( char& i : key){
        if (isupper(i)){
            cout << "Error! The encryption key must contain only lower case characters.";
      }}
    cout << endl;

    for( char letter = 'a'; letter < 'z'; ++letter ){
        string::size_type test = key.find(letter);
        if (test == string::npos){
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        } else {
            cout << "yup" << endl;
        }

    }
    cout << endl;



 //     else if (){
 //       cout << "Error! The encryption key must contain only lower case characters." << endl;
 //
 //   }
    cout << "Enter the text to be encrypted: ";
    cin >> text;


    cout << "Encrypted text: " <<key << " " << text << endl;
    return EXIT_SUCCESS;
}
