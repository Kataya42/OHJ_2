#include "instance.hh"
#include "course.hh"

Instance::Instance(Date &today, Course *course, std::string name):
    name_(name),
    started_(today)
{
    parent_course_ = course;
}

void Instance::print()
{
    std::cout << name_ << std::endl << INDENT << "Starting date: ";
    started_.print();
    std::cout << std::endl << INDENT <<  "Amount of students: " <<
                 students_.size() << std::endl;
}

void Instance::print_students()
{
    for ( auto student : students_ ){
        std::cout << INDENT;
        student->print();
    }
}

bool Instance::is_named(std::string name)
{
   return name == name_;
}

void Instance::add_student(Account *student, Date &today)
{
    // if the Account is already registered in this instance
    if ( std::find(students_.begin(),
                   students_.end(), student) != students_.end() ){
        std::cout << ALREADY_REGISTERED << std::endl;

    // else if signup date has passed
    } else if ( started_ < today ){
        std::cout << LATE << std::endl;

    } else {
        student->add_to_current(this);
        students_.push_back(student);
    }
}

std::string Instance::get_name()
{
    return name_;
}

Course *Instance::get_course()
{
    return parent_course_;
}

