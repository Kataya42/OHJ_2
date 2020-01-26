#include <iostream>
using namespace std;


int main()

{
  int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    if (number < 0 ){
      cout << "Error!" << endl;
    } else if(number == 0){
        cout << "The cube of 0 is 0." << endl;
    }else {
      int cube = number * number * number;
      int test = cube / number / number;
      if (test == number){
     cout << "The cube of " << number << " is " << cube << "." << endl;
      } else {
    cout << "The cube of " << number << " is not " << cube << "." << endl;
      }
    }
    return 0;
}
