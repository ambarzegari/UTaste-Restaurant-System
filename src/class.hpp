#ifndef DISTRICT_HPP
#define DISTRICT_HPP

#include "General.hpp"

class User;
class Reserve;

class MenuItem
{
private:
    string name;
    int price;
public:
    MenuItem(string n, int p);
    string GetName();
};

class Resturant
{
private:
    string name;
    vector<MenuItem *> menu_item;
    int opening_time;
    int closing_time;
    int number_of_tables;
    int Reserve_num;
    vector<Reserve*> reserve;

public:
    Resturant(string n, string menu, int op, int cl, int num);
    string GetName();
    bool HaveFoodInMenu(string fn);
    void AddReserve(Resturant* res, User* us, int st, int et, int tid, vector<MenuItem*> f);
    void ReserveHandler(vector<string> requests, User* user, Resturant* res);
};

class District
{
private:
    string name;
    vector<District *> neighbors;
    vector<Resturant *> resturants;

public:
    District(string n);
    string GetName();
    void AddNeighbors(District *nei);
    void AddResturant(string name, string menu, int op, int cl, int num);
    bool CheckNeighbor();
    void PrintDistrictInfo();
    vector<District*> GetNeighbor();
    void ShowAllResturantsInDistrict();
    void ShowSomeResturantsInDistrict(string fn);
    void SortResturantsVector();
    Resturant* FindRestaurant(string name);

};

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

class Reserve
{
private:
    Resturant* restaurant;
    User* user;
    int start_time;
    int end_time;
    int table_id;
    int reserve_id;
    vector<MenuItem*> foods;

public:
    Reserve(Resturant* res, User* us, int st, int et, int tid, int reserve, vector<MenuItem*> f);
    int GetStartTime() { return start_time; };
    int GetEndTime() { return end_time; };
    int GetTableID() { return table_id; };
    int GetReserveID() { return reserve_id; };
};

#endif