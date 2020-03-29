#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle)
{
    cycle_ = cycle;
}

Queue::~Queue()
{
    Vehicle* sukkeli;

    while ( first_ != nullptr ) {

        sukkeli = first_;
        first_ = first_->next;

        delete sukkeli;
    }
}

void Queue::enqueue(string reg)
{

    if (is_green_ == true) {

        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
        return;
    }

    Vehicle* new_car = new Vehicle({reg, nullptr});

    if (last_ == nullptr && first_ == nullptr) {

        first_ = new_car;
        last_ = new_car;
    }

    else {
        last_->next = new_car;
        last_ = new_car;
    }
}

void Queue::switch_light()
{
    (is_green_) ? (is_green_ = false) : (is_green_ = true);

    if (is_green_ == true && first_ == nullptr) {

        std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
    }

    else if (is_green_ == false && first_ == nullptr) {

        std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
    }

    else if (is_green_ == true) {

        std::cout << "GREEN: Vehicle(s) ";

        for (unsigned int i = 0; i < cycle_; i++) {

            Vehicle* current_first = first_;

            std::cout << current_first->reg_num << " ";

            if ( first_ == last_ ) {
                first_ = nullptr;
                last_ = nullptr;
                delete current_first;
                break;
            }

            first_ = current_first->next;

            delete current_first;
        }

        std::cout << "can go on" << std::endl;

        is_green_ = false;
    }

}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print()
{
    if (is_green_ == true && first_ == nullptr) {

        std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
    }

    else if (is_green_ == false && first_ == nullptr) {

        std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
    }

    else if (is_green_ == false) {

        std::cout << "RED: Vehicle(s) ";
        Vehicle* next_car = first_;

        while ( next_car != nullptr ) {
            std::cout << next_car->reg_num << " ";
            next_car = next_car->next;
        }

        std::cout << "waiting in traffic lights" << std::endl;
    }
}
