#include "instance.hh"
#include "course.hh"

Instance::Instance(Course *course, std::string name){
    main_ = course;
    name_ = name;
}

void Instance::print(){

}

void Instance::print_students(){

}

bool Instance::is_named(std::string name ){

}
