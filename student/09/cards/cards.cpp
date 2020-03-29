#include "cards.hh"
using namespace std;
// TODO: Implement the methods here

Cards::Cards(): top_(nullptr) {
    top_ = nullptr;
    bottom_ = nullptr;

}

Cards::~Cards() {
    while ( top_ != nullptr) {
        Card_data* item = top_;
        top_ = top_ ->next;

        delete item;
    }
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
    if ( top_ == nullptr )
        return;

    Card_data* temp = top_;
    int running_number = 1;

    while ( temp != nullptr ) {
       s << running_number << ". " << temp->data << endl;
       temp = temp ->next;
       ++running_number;
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
    if (top_ == nullptr || bottom_ == top_)
        return false;

    Card_data * temp = top_;

    while( ! (temp->next == bottom_))
        temp = temp ->next;

    bottom_ -> next = top_;
    top_ = bottom_;
    bottom_ = temp;
    bottom_ -> next = nullptr;

    return true;
}

bool Cards::top_to_bottom() {
    if (top_ == nullptr || bottom_ == top_)
        return false;

    bottom_ -> next = top_;
    bottom_ = top_;
    top_ = bottom_ -> next;
    bottom_ -> next = nullptr;

    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s) {

    if (top_ == nullptr)
        return;

    Card_data* temp = top_;
    recursive_print(temp, s);

}

static int num = 1;
int Cards::recursive_print(Cards::Card_data *top, std::ostream &s) {

    if (top == nullptr)
        return false;

    recursive_print(top->next,s);
    s << num << ": " << top->data << endl;
    num++;
    return true;
}
