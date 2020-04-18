#include "instance.hh"
#include "course.hh"

Instance::Instance(Date today, Course *course, std::string name){
    main_ = course;
    name_ = name;
    started_ = today;

}

void Instance::print(){
    std::cout << name_ << std::endl << INDENT << "Starting date: ";
    started_.print();
    std::cout << std::endl << INDENT <<  "Amount of students: " << students_.size() << std::endl;

}

void Instance::print_students(){

    for (auto student : students_){
        student->print();
    }

}

bool Instance::is_named(std::string name ){
    if (name == name_){
        return true;
    } else {
        return false;
    }

}
