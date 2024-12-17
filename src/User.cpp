#include "User.hpp"

User::User(string username_, string password_)
{
    username = username_;
    password = password_;

    state = IN_APP;
}

bool User::CheckUsername(string username_)
{
    return username == username_;
}

bool User::CheckPassword(string password_)
{
    return password == password_;
}