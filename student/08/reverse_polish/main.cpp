#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

vector <string > split(const string &s,
    const char &delimiter, bool ignore_empty = false) {

    vector < string > result;
    string tmp = s;

    while (tmp.find(delimiter) != string::npos) {

        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());

        if (not(ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }

    if (not(ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }

    return result;
}

int calculate(int & a, int & b, string oper){

    int result;
    if(oper == "/" && b == 0){
        result = -99;
        return result;
    }

    if(oper == "+"){
        result = a + b;
    } else if(oper == "-"){
        result = a - b;
    } else if(oper == "/"){
        result = a / b;
    } else if(oper == "*"){
        result = a * b;
    } else {
        result = __INT_MAX__;
    }

    return result;
}

int main() {

    vector<string> all;
    vector<string> operators;
    vector<int> numbers;
    string input;

    cout << "Input an expression in reverse Polish notation (end with #): " << endl;
    cout << "EXPR> ";
    getline(cin, input);

    all = split(input, ' ', false);

    for (auto c : all){
        if (is_digits(c)){
            int n = stoi(c);
            numbers.push_back(n);
        } else {
            operators.push_back(c);
        }
    }

    int result;
    int a = 0;
    // int b = 0;
    operators.pop_back();

    if (not is_digits(all[0])){
        cout << "Error: Expression must start with a number" << endl;
        return EXIT_FAILURE;
    }

    if (numbers.size() - operators.size() > 1){
        cout << "Error: Too few operators" << endl;
        return EXIT_FAILURE;
    } else if(numbers.size() - operators.size() < 1 ){
        cout << "Error: Too few operands" << endl;
        return EXIT_FAILURE;
    } else {



        reverse(numbers.begin(),numbers.end());

        for (unsigned int i = 0 ; i < operators.size(); i++){
            if (a == 0){
                a = calculate(numbers[i],numbers[i+1],operators[i]);
                result = a;

                if (result == -99 ){
                    cout << "Error: Division by zero" << endl;
                    return EXIT_FAILURE;
                } else if( result == __INT_MAX__){
                    cout << "Error: Unknown character" << endl;
                    return EXIT_FAILURE;
                }

            } else {
                result = calculate(a, numbers[i+1], operators[i]);
            }

        }

        if (result == __INT_MAX__){
            cout << "Error: Unknown character" << endl;
            return EXIT_FAILURE;
        } else if(result == -99){
            cout << "Error: Division by zero" << endl;
            return EXIT_FAILURE;
        } else{
            // result = calculate(numbers[0],numbers[1],operators[0]);
            cout << "Correct: "<< result << " is the result"<< endl;

        }

    }


    return EXIT_SUCCESS;

}
