#include "player.hh"
#include <string>
#include <iostream>

using namespace std;

Player::Player(string name):
    name_(name), points_(0){
}

string Player::get_name() const{
    return name_;
}
void Player::add_points(int pts){
    points_ += pts;

    if ( points_ > 50){
        points_ = 25;
        cout << name_<< " gets penalty points!" << endl;

    }
}
int Player::get_points(){
    return points_;
}

bool Player::has_won(){
    if (points_ == 50){
        return true;
    } else {
        return false;
    }
}
