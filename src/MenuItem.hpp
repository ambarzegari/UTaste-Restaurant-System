#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include "General.hpp"

class MenuItem
{
private:
    string name;
    int price;
public:
    MenuItem(string n, int p);
    string GetName();
    int Getprice() { return price; };
};

#endif