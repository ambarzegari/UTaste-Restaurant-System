#ifndef Utaste_HPP
#define Utaste_HPP

#include "User.hpp"
#include "District.hpp"
#include "Resturant.hpp"

class UTaste
{
private:
    vector<User *> app_users;
    User *user;
    vector<District *> districts;

public:
    UTaste();
    void GetDataFromResturantsFile(char argv[]);
    void GetDataFromDistrictsFile(char argv[]);
    void IoHandler();

    void POSTHandler(vector<string> requests);
    void SignUp(vector<string> requests);
    void LogOut(vector<string> requests);
    void LogIn(vector<string> requests);

    void PUTHandler(vector<string> requests);
    void SetUserDistrict(vector<string> requests);

    void DELETEHandler(vector<string> requests);

    void GETHandler(vector<string> requests);
    void ShowDistrict(vector<string> requests);
    void ShowResturantsList(vector<string> requests);
};

#endif