#ifndef DISTRICT_HPP
#define DISTRICT_HPP

#include "General.hpp"

class District
{
private:
    string name;
    vector<District *> neighbors;

public:
    District(string n);
    string GetName();
    void AddNeighbors(District * nei);
};

#endif