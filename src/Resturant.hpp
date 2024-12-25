#ifndef RESTURANT_HPP
#define RESTURANT_HPP

#include "General.hpp"
#include "MenuItem.hpp"

class Resturant
{
private:
    string name;
    vector<MenuItem *> menu_item;
    int opening_time;
    int closing_time;
    int number_of_tables;

public:
    Resturant(string n, string menu, int op, int cl, int num);
    string GetName();
};

#endif
