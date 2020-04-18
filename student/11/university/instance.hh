/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance of a course.
 *
 * Program author:
 * Name: Aleksi Rissa
 * Student number: 292053
 * UserID: xfalri
 * E-Mail: aleksi.rissa@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */
#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <utils.hh>

// Forward-declaration of Course, so that instance can point to the course it belongs to.
class Course;
class Date;

const std::string ALREADY_REGISTERED = "Error: Student has already registered on this course.";
const std::string LATE = "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";

class Instance
{
public:
    Instance(Date today, Course *course, std::string name);
    void print();
    void print_students();
    bool is_named(std::string name);

private:
    std::string name_;
    Course* main_;
    Date started_= utils::today;
    std::vector<Account*> students_;

};

#endif // INSTANCE_HH
