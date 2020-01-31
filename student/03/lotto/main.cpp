#include <iostream>

using namespace std;
unsigned long int nume(int total_balls){

    unsigned long int numerator = 1;

    for (int a=1;a<=total_balls;a++) {
            numerator=numerator*a;
        }
    return numerator;
}


unsigned long int deno(int total_balls, int drawn_balls){

    int difference= total_balls - drawn_balls;
    unsigned long int fact_d = 1;
    unsigned long int fact_diff = 1;


    for (int a=1;a<=drawn_balls;a++) {
            fact_d=fact_d*a;
        }
    for (int a=1;a<=difference;a++) {
            fact_diff=fact_diff*a;
        }

    unsigned long int denominator = fact_diff * fact_d;

    return denominator;
}

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

    } else if(drawn_balls > total_balls){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    } else {
        unsigned long int numerator = nume(total_balls);
        unsigned long int denominator = deno(total_balls, drawn_balls);
        unsigned long int probability = numerator / denominator;
        cout << "The probability of guessing all "<< drawn_balls << " balls correctly is 1/" << probability << endl;
    }

    return 0;
}
