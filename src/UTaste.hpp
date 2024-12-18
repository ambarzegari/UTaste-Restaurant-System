#ifndef Utaste_HPP
#define Utaste_HPP

#include "User.hpp"

class UTaste
{
private:
    vector<User*> app_users;
    User* user; 

public:
    UTaste();
    void IoHandler();

    void POSTHandler(vector<string> requests);
    void SignUp(vector<string> requests);
    void LogOut(vector<string> requests);
    void LogIn(vector<string> requests);

    void PUTHandler(vector<string> requests);
    void DELETEHandler(vector<string> requests);
    void GETHandler(vector<string> requests);

};




#endif