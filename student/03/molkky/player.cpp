#include "player.hh"
#include <string>
#include <iostream>

using namespace std;

Player::Player(string name):
    name_(name){
}
string Player::get_name() const{
    return name_;
}
int Player::get_points(){
    return points_;
}
void Player::add_points(int pts){
    points_ += pts;

    if ( points_ > 50){
        cout << name_<< " gets penalty points!" << endl;
        points_ = 25;
    }
}
int Player::has_won(){
    if (points_ == 50){
        return 1;
    } else {
        return 0;
    }
}
