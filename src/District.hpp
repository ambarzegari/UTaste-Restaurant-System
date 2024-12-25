#ifndef DISTRICT_HPP
#define DISTRICT_HPP

#include "General.hpp"
#include "Resturant.hpp"

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
};

#endif