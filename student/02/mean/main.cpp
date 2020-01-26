#include <iostream>
using namespace std;
// Write here a function counting the mean value

int main()
{
  int count = 0;
  int number = 0;
  float measurement = 0;
    cout << "From how many integer numbers you want to count the mean value? ";
    cin >> count;
    if ( count < 1 ){
      cout << "Cannot count mean value from " << count << " numbers" << endl;
    } else {
      while (number < count){
	number += 1;
	cout << "Input " << number << ". number: ";
	cin >> measurement;
      }
    }
}
