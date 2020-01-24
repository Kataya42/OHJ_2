#include <iostream>

using namespace std;

int main()
{
  int temp = 0;
  std::cout << "Enter a temperature: ";
  std::cin >> temp;
  double faren = temp * 1.8 + 32;
  double cel =( temp - 32) / 1.8;


  std::cout << temp << " degrees Celsius is "<< faren <<" degrees Fahrenheit" << std::endl;;
std::cout << temp << " degrees Fahrenheit is "<< cel <<" degrees Celsius" << std::endl;;
    return 0;
}
