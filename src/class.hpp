#ifndef DISTRICT_HPP
#define DISTRICT_HPP

#include "General.hpp"

class User;
class Reserve;
class Resturant;
class District;
class MenuItem;
class Discount;
class TotalPriceDiscount;
class FirstOrderDiscount;
class FoodDiscount;

class Resturant
{
private:
    string name;
    vector<MenuItem *> menu_item;
    int opening_time;
    int closing_time;
    int number_of_tables;
    int Reserve_num;
    vector<Reserve *> reserve;
    TotalPriceDiscount *total_price_discount;
    FirstOrderDiscount *first_order_discount;

public:
    Resturant(string n, string menu, int op, int cl, int num);
    string GetName();
    bool HaveFoodInMenu(string fn);
    void AddReserve(Resturant *res, User *us, int st, int et, int tid, vector<MenuItem *> f);
    void ReserveHandler(vector<string> requests, User *user, Resturant *res);
    void DeleteReserve(int res_id, User *user);
    void ShowReserve(User *user, int res_id);
    void SortMenuItemVector();
    void ShowRestaurantInfo(District *dist);
    void AddTotalDiscount(string t_, int min_, int dis_);
    void AddFirstOrderDiscount(string t_, int dis_);
    MenuItem *FindMenuItem(string n_);
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
    vector<District *> GetNeighbor();
    void ShowAllResturantsInDistrict();
    void ShowSomeResturantsInDistrict(string fn);
    void SortResturantsVector();
    Resturant *FindRestaurant(string name);
    void ShowAllReserve(User *user);
    void ShowOneReserve(User *user, int res_id);
    vector<Resturant *> GetRestaurants() { return resturants; };
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
    int budget;
    District *district;

public:
    User(string username_, string password_);
    bool CheckUsername(string username_);
    bool CheckPassword(string password_);
    void ChangeStateToLoggedOut();
    void ChangeStateToInApp();
    void SetDistrict(District *dist);
    District *GetDistrict();
    void SetBudget(int b);
    int GetBudget();
    void ReduceBudget(int n);
};

class Reserve
{
private:
    Resturant *restaurant;
    User *user;
    int start_time;
    int end_time;
    int table_id;
    int reserve_id;
    int original_price;
    int first_order_dis;
    int total_item_dis;
    int total_price_dis;
    vector<MenuItem *> foods;

public:
    Reserve(Resturant *res, User *us, int st, int et, int tid, int reserve, vector<MenuItem *> f);
    int GetStartTime() { return start_time; };
    int GetEndTime() { return end_time; };
    int GetTableID() { return table_id; };
    int GetReserveID() { return reserve_id; };
    User *GetUser() { return user; };
    void Show();
    void SetDiscount(int original, int first_order, int total_item, int total_price);
    int GetTotalPrice() { return original_price - first_order_dis - total_item_dis - total_price_dis; }
};

class MenuItem
{
private:
    string name;
    int price;
    FoodDiscount *food_discount;

public:
    MenuItem(string n, int p);
    string GetName();
    int Getprice();
    void AddFoodDiscount(string t_, int dis_);
    FoodDiscount *GetFoodDiscount() { return food_discount; }
};

class Discount
{
protected:
    string type;
    int discount;

public:
    Discount(string t_, int dis_);
    virtual string GetType() { return type; }
    virtual int GetDiscount() { return discount; }
    virtual int CalculateDiscount(int price);
};

class TotalPriceDiscount : public Discount
{
private:
    int minimum;

public:
    TotalPriceDiscount(string t_, int dis_, int min_);
    int GetMinimum() { return minimum; }
};

class FirstOrderDiscount : public Discount
{
public:
    FirstOrderDiscount(string t_, int dis_);
};

class FoodDiscount : public Discount
{
public:
    FoodDiscount(string t_, int dis_);
};

#endif