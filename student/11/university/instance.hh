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
 * The program has been implemented to mirror the style of the
 * already existing code. For example university.cpp has some
 * repetitiveness with searching does a certain element exsist,
 * I decided to leave it like that to make the style uniform with
 * the pre-existing code, instead of implementing a does_exist method
 * what would have been added to only to the few methods I implemented.
 *
 * Since students are not removed from the instance list when they complete
 * courses the checks are made in this class instead of Account class,
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
    /**
     * @brief Instance constructor
     * @param Date today, signup date for instanced.
     * @param Course, pointer to parent course.
     * @param name
     */
    Instance(Date &today, Course *course, std::string name);
    /**
     * @brief print
     * Print instance name, signup date and the amount of Accounts in it.
     */
    void print();
    /**
     * @brief print_students
     * Prints account information for each account in this instance.
     */
    void print_students();
    /**
     * @brief is_named
     * @param name
     * @return true if the name matches, false otherwise.
     * Checks if the name of this is instance is the one queried.
     */
    bool is_named(std::string name);
    /**
     * @brief add_student
     * @param Account, pointer to account in to be added
     * @param Date, what is current date
     * Checks if student has already registered, gives an error if so
     * also checks has signup date passed, gives an different error if so
     * Else adds account into students_, also calls Account to add this
     * instance into its current ongoing course instances.
     */
    void add_student(Account *student, Date &today);
    /**
     * @brief get_name
     * @return the name of this instance.
     */
    std::string get_name();
    /**
     * @brief get_course
     * @return the name of the parent course.
     */
    Course* get_course();

private:

    const std::string name_;
    // Date when this instance was created.
    const Date started_= utils::today;
    // Pointer to course this instance belongs to.
    Course* parent_course_;
    // Accounts registered on this instance.
    std::vector<Account*> students_;

};

#endif // INSTANCE_HH
