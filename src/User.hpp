#ifndef USER_HPP
#define USER_HPP

#include "General.hpp"

enum State
{
    IN_APP,
    LOGGED_OUT
};

class User
{
private:
    State state;
    string username;
    string password;

public:
    User(string username_, string password_);
    bool CheckUsername(string username_);
    bool CheckPassword(string password_);
    void ChangeStateToLoggedOut();
    void ChangeStateToInApp();
};




#endif