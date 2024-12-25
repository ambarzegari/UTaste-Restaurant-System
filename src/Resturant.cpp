#include "Resturant.hpp"

Resturant::Resturant(string n, string menu, int op, int cl, int num)
{
    name = n;
    opening_time = op;
    closing_time = cl;
    number_of_tables = num;

    stringstream X(menu);
    string food_and_price;

    while (getline(X, food_and_price, ';'))
    {
        stringstream Y(food_and_price);
        string word, food;
        int price;
        for (int i = 1;getline(Y, word, ':'); i++)
        {
            if (i==1)
            {
                food = word;
            }
            if (i==2)
            {
                price = stoi(word);
            }
        }
        menu_item.push_back(new MenuItem(food, price));
    }
    
}