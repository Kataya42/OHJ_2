#include <iostream>

using namespace std;

int main()
{
    int total_balls;
    int drawn_balls;
    cout << "Enter the total number of lottery balls: ";
    cin >> total_balls;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn_balls;

    if (total_balls < 0 or drawn_balls < 0){
        cout << "The number of balls must be a positive number." << endl;
    } else{
        cout << "Heyy it works" << endl;
    }

    return 0;
}
