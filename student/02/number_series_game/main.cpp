#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    std::cout << "How many numbers would you like to have? ";
    cin >> number;
    
    int i = 0;
    while(i < number){
      ++i;
      cout << i << endl;
    }
}
