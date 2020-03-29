#include "queue.hh"
#include <iostream>
#include <string>
using namespace std;

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle) {
    first_ = nullptr;
    last_ = nullptr;
    cycle_ = cycle;
}

Queue::~Queue() {

}

void Queue::enqueue(string reg) {

    if (is_green_){
        cout << "The vehicle " << reg << " need not stop to wait" << endl;
    } else {
        Vehicle* new_car = new Vehicle{reg, nullptr};

       if ( first_ == nullptr ) {
          first_ = new_car;
          last_ = new_car;
       } else {
          Vehicle* newc = first_;
          first_ = new_car;
          first_ -> next = newc;
       }
    }
}

void Queue::dequeue(){

    if ( first_ == nullptr) {
        return;
    } else if (first_ == last_) {

        Vehicle * temp = first_;

        temp = first_;
        first_= first_->next;
        free(temp);
        return;
    }

        Vehicle * temp_node = first_;

        while (!(temp_node->next == last_)) {
            temp_node = temp_node -> next;
        }

        last_ -> next = first_;
        first_ = last_;
        last_ = temp_node;
        last_->next = nullptr;

        Vehicle * temp = first_;
        temp = first_;
        first_= first_->next;
        free(temp);
}


int Queue::recursive(Queue::Vehicle *first) {

    if (first  == nullptr){
           return false;
        }

    recursive(first->next);
    cout << first->reg_num << " ";
    return true;
}

void Queue::switch_light() {

    if (!(is_green_)) {
        print();
    } else {
        print();
        unsigned int current_cycle = 0;
        while (current_cycle < cycle_) {
            dequeue();
            ++current_cycle;

        }
    }
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

void Queue::print() {

    if ( first_ == nullptr && is_green_){
           cout << "GREEN: No vehicles waiting in traffic lights" << endl;
           is_green_ = false;
           return;
    } else if(first_ == nullptr){
        cout << "RED: No vehicles waiting in traffic lights" << endl;
        is_green_ = true;
        return;
    }

    if (is_green_){
       cout << "GREEN: Vehicle(s) ";
    } else{
       cout << "RED: Vehicle(s) ";
    }

    Vehicle* temp_node = first_;
    recursive(temp_node);


    if (is_green_){
        cout << "can go on" << endl;
        is_green_ = false;
    } else {
        cout << "waiting in traffic lights" << endl;
        is_green_ = true;
    }
}
