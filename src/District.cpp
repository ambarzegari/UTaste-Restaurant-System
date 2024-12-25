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

void District::AddResturant(string name, string menu, int op, int cl, int num)
{
    resturants.push_back(new Resturant(name, menu, op, cl, num));
}

bool District::CheckNeighbor()
{
    return neighbors.empty();
}

void District::PrintDistrictInfo()
{
    cout << name << ": ";

    for (int i = 0; i < neighbors.size(); i++)
    {
        cout << neighbors[i]->GetName();
        if (i < neighbors.size() - 1)
        {
            cout << ", ";
        }
        else
        {
            cout << endl;
        }
    }
}
