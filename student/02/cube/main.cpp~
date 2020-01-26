#include <iostream>
using namespace std;


void mean(float sum, float count) {
    float mean = 0;
    mean = sum / count;
    cout << "Mean value of the given numbers is " << mean << endl;

}

int main()
{
  int count = 0;
  int number = 0;
  int measurement = 0;
  int sum = 0;
    cout << "From how many integer numbers you want to count the mean value? ";
    cin >> count;
    if ( count < 1 ){
      cout << "Cannot count mean value from " << count << " numbers" << endl;
    } else {
      while (number < count){
	number += 1;
	cout << "Input " << number << ". number: ";
	cin >> measurement;
	sum = sum + measurement;
      }
      mean(sum, count);
    }
}
