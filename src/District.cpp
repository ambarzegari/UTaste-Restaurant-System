#include "District.hpp"

District::District(string n)
{
    name = n;
    neighbors = {};
}

string District::GetName()
{
    return name;
}

void District::AddNeighbors(District *nei)
{
    neighbors.push_back(nei);
}
