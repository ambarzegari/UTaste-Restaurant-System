#ifndef USER_HPP
#define USER_HPP

#include "General.hpp"
#include "District.hpp"

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
    District* district;

public:
    User(string username_, string password_);
    bool CheckUsername(string username_);
    bool CheckPassword(string password_);
    void ChangeStateToLoggedOut();
    void ChangeStateToInApp();
    void SetDistrict(District* dist);
    District* GetDistrict();
};




#endif