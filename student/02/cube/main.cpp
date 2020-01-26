#include <iostream>
using namespace std;


int main()

{
  int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    if (number < 1 ){
      cout << "Error!" << endl;
    } else {
      cout << "The cube of " << number << " is " << number * number * number << endl;
    }
}
