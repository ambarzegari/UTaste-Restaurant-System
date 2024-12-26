#include "MenuItem.hpp"

MenuItem::MenuItem(string n, int p)
{
    name = n;
    price = p;
}

string MenuItem::GetName()
{
    return name;
}