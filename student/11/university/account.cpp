#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number)
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

void Account::add_instance(Instance *inst)
{
    current_.push_back(inst);
    std::cout << SIGNED_UP << std::endl;
}

bool Account::complete_course(Instance *inst, Course *course)
{
    if (!(std::find(current_.begin(), current_.end(), inst) != current_.end())){
            std::cout << NO_SIGNUPS<< std::endl;
            return false;
    } else {
        current_.erase(std::remove(current_.begin(), current_.end(), inst), current_.end());
        completed_.push_back(course);
        std::cout << COMPLETED << std::endl;
        return true;
    }

}

void Account::print_complete()
{
    int running_number = 0;
    std::cout << "Completed:" << std::endl;
    for (auto course : completed_){
        course->print_info(true);
        running_number ++;
    }
    std::cout << "Total credits: " << running_number * CREDIT << std::endl;
}

void Account::print_current()
{
    std::cout << "Current:" << std::endl;
    for (auto instance : current_){
        instance->main_->print_info(false);
        std::cout << " " << instance->name_ << std::endl;
    }
    print_complete();
}
