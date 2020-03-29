#include "cards.hh"
using namespace std;
// TODO: Implement the methods here

Cards::Cards(): top_(nullptr) {

}

Cards::~Cards() {

}

void Cards::add(int id) {

   Card_data* new_item = new Card_data{id, nullptr};

    if ( top_ == nullptr ) {
       top_ = new_item;
       bottom_ = new_item;

    } else {
       Card_data* new_shit = top_;
       top_ = new_item;
       top_ ->next = new_shit;
    }
}

void Cards::print_from_top_to_bottom(std::ostream &s) {

    Card_data* item_to_be_printed = top_;
    int running_number = 1;

    while ( item_to_be_printed != nullptr ) {
       s << running_number << ". " << item_to_be_printed->data << endl;
       ++running_number;
       item_to_be_printed = item_to_be_printed->next;
    }
}

bool Cards::remove(int &id) {
    if ( top_ == nullptr )
        return false;

    Card_data * temp = top_;

    id = temp -> data;
    top_ = top_->next;
    delete temp;

    return true;

}

bool Cards::bottom_to_top() {

}

bool Cards::top_to_bottom() {

}

void Cards::print_from_bottom_to_top(std::ostream &s) {

}



int Cards::recursive_print(Cards::Card_data *top, std::ostream &s) {

}
