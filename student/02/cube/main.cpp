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
