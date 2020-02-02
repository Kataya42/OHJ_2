#include <iostream>

using namespace std;

int main()
{
    string key;
    string text;
    cout << "Enter the encryption key: ";
    cin >> key;
    cout << "Enter the text to be encrypted: ";
    cin >> text;


    cout << "Encrypted text: " <<key << " " << text << endl;
    return EXIT_SUCCESS;
}
