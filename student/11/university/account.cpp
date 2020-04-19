#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number),
    credits_(0)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email()
{
    return email_;
}

void Account::add_to_current(Instance *instance)
{
    current_.push_back(instance);
    std::cout << SIGNED_UP << std::endl;
}

void Account::complete_course(Instance *instance)
{
    // if course instance is not currently ongoing
    if ( !(std::find(current_.begin(),
                     current_.end(), instance) != current_.end()) ){

        std::cout << NO_SIGNUPS << std::endl;

    } else {
        completed_.push_back(instance->get_course());
        current_.erase(std::remove(current_.begin(),
                                   current_.end(), instance), current_.end());

        std::cout << COMPLETED << std::endl;

        credits_ += instance->get_course()->get_credits();

    }
}

void Account::print_complete()
{
    // for courses that have been completed
    for ( auto course : completed_ ){
        course->print_info(true);
    }

    std::cout << "Total credits: " << credits_ << std::endl;
}

void Account::print_current()
{
    std::cout << "Current:" << std::endl;

    // for course instances that are currently ongoing
    for ( auto instance : current_ ){
        instance->get_course()->print_info(false);
        std::cout << " " << instance->get_name() << std::endl;
    }

    std::cout << "Completed:" << std::endl;
    print_complete();
}
