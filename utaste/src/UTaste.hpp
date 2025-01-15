#ifndef Utaste_HPP
#define Utaste_HPP

#include "class.hpp"

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
    void GetDataFromDiscountsFile(char argv[]);
    void CheckUserLogin();

    void SignUp(string u, string p);
    void LogOut(vector<string> requests);
    void LogIn(vector<string> requests);
    void ReserveHandler(vector<string> requests);
    void IncreaseBudget(vector<string> requests);

    void SetUserDistrict(vector<string> requests);

    void DeleteReserve(vector<string> requests);

    void ShowDistrict(vector<string> requests);
    void ShowResturantsList(vector<string> requests);
    void ShowReserve(vector<string> requests);
    void ShowRestaurantInfo(vector<string> requests);
    void ShowBudget(vector<string> requests);

    User* GetUser(){ return user; }
};

#endif