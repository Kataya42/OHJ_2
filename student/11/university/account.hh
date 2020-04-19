/* Class: Account
  * ----------
  * Defines a student or a staff account in the university system.
  *
  * In the project, this class should be expanded to
  * include study history of the account.
  * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();
    /**
     * @brief add_to_current
     * @param Instance: pointer to instance
     * Adds course instance into current_
     */
    void add_to_current(Instance* instance);
    /**
     * @brief complete_course
     * @param Instance: pointer to instance
     * Checks and gives an error if user is not in given course
     * instance, else removes course instance from current_ and
     * adds course into completed_ and prints successful course
     * complted message. Also updates account credit score.
     */
    void complete_course(Instance* instance);
    /**
     * @brief print_complete
     * Prints information on all complete courses
     */
    void print_complete();
    /**
     * @brief print_current
     * Prints information on all current course instances
     * also calls print_complete() to print its information.
     */
    void print_current();

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    std::vector<Instance*> current_;
    std::vector<Course*> completed_;
    // total credits
    int credits_;
};

#endif // ACCOUNT_HH
