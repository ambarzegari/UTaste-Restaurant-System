#ifndef Utaste_HPP
#define Utaste_HPP

#include "User.hpp"

class Utaste
{
private:
    vector<User*> app_users;
    User* user = NULL; 

public:
    Utaste();
    void IoHandler();
};




#endif