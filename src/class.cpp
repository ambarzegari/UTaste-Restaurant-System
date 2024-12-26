#include "class.hpp"

Reserve::Reserve(Resturant *res, User *us, int st, int et, int tid, int reserve, vector<MenuItem *> f)
{
    restaurant = res;
    user = us;
    start_time = st;
    end_time = et;
    table_id = tid;
    reserve_id = reserve;
    foods = f;

    cout << "Reserve ID: " << reserve_id << endl;
}
void Reserve::Show()
{
    cout << reserve_id << ": " << restaurant->GetName() << " " << table_id << " " << start_time << "-" << end_time << " ";

    map<MenuItem *, int> food_rep;

    for (auto f : foods)
    {
        food_rep[f]++;
    }

    for (auto fr : food_rep)
    {
        cout << fr.first->GetName() << "(" << fr.second << ")" << " ";
    }

    cout << endl;
}

Resturant::Resturant(string n, string menu, int op, int cl, int num)
{
    name = n;
    opening_time = op;
    closing_time = cl;
    number_of_tables = num;
    Reserve_num = 0;

    stringstream X(menu);
    string food_and_price;

    while (getline(X, food_and_price, ';'))
    {
        stringstream Y(food_and_price);
        string word, food;
        int price;
        for (int i = 1; getline(Y, word, ':'); i++)
        {
            if (i == 1)
            {
                food = word;
            }
            if (i == 2)
            {
                price = stoi(word);
            }
        }
        menu_item.push_back(new MenuItem(food, price));
    }
}

string Resturant::GetName()
{
    return name;
}

bool Resturant::HaveFoodInMenu(string fn)
{
    for (auto mi : menu_item)
    {
        if (mi->GetName() == fn)
        {
            return true;
        }
    }
    return false;
}

void Resturant::AddReserve(Resturant *res, User *us, int st, int et, int tid, vector<MenuItem *> f)
{

    for (auto res : reserve)
    {
        if (res->GetTableID() == tid)
        {
            if ((res->GetStartTime() <= st && st < res->GetEndTime()) ||
                (res->GetStartTime() < et && et <= res->GetEndTime()) ||
                ((res->GetEndTime() <= et) && (res->GetStartTime() >= st)))
            {
                throw runtime_error(PERMISSION_DENIED);
            }
        }
    }
    if (st < opening_time || et > closing_time)
    {
        throw runtime_error(PERMISSION_DENIED);
    }

    Reserve_num++;
    reserve.push_back(new Reserve(res, us, st, et, tid, Reserve_num, f));
}

void Resturant::ReserveHandler(vector<string> requests, User *user, Resturant *rest)
{
    vector<MenuItem *> f = {};

    stringstream X(requests[12]);
    string food_name;

    while (getline(X, food_name, ','))
    {
        for (auto menu : menu_item)
        {
            if (menu->GetName() == food_name)
            {
                f.push_back(menu);
            }
        }
    }

    rest->AddReserve(rest, user, stoi(requests[8]), stoi(requests[10]), stoi(requests[6]), f);
}

void Resturant::DeleteReserve(int res_id, User *user)
{
    for (auto res : reserve)
    {
        if (res->GetReserveID() == res_id)
        {
            if (res->GetUser() != user)
            {
                throw runtime_error(PERMISSION_DENIED);
            }
            reserve.erase(find(reserve.begin(), reserve.end(), res));
            delete res;
            cout << OK << endl;
            return;
        }
    }
    throw runtime_error(NOT_FOUND);
}

void Resturant::ShowReserve(User *user, int res_id = 0)
{
    for (auto res : reserve)
    {
        if (res->GetUser() == user)
        {
            if (res_id == 0)
            {
                res->Show();
            }
            else
            {
                if (res->GetReserveID() == res_id)
                {
                    res->Show();
                }
            }
        }
    }
}

void Resturant::SortMenuItemVector()
{
    sort(menu_item.begin(), menu_item.end(),
         [](MenuItem *left, MenuItem *right)
         { return left->GetName() < right->GetName(); });
}

void Resturant::ShowRestaurantInfo(District *dist)
{
    cout << "Name: " << name << "\n"
         << "District: " << dist->GetName() << "\n"
         << "Time: " << opening_time << "-" << closing_time << "\n"
         << "Menu: ";
    for (auto item : menu_item)
    {
        if (item != *menu_item.begin())
        {
            cout << ", ";
        }
        cout << item->GetName() << "(" << item->Getprice() << ")";
    }

    cout << endl;

    for (int i = 1; i <= number_of_tables; i++)
    {
        cout << i << ": ";
        int j = 0;
        for (auto res : reserve)
        {

            if (res->GetTableID() == i)
            {
                if (j != 0)
                {
                    cout << ", ";
                }
                cout << "(" << res->GetStartTime() << "-" << res->GetEndTime() << ")";
                j++;
            }
        }
        cout << endl;
    }
}

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

vector<District *> District::GetNeighbor()
{
    return neighbors;
}

void District::ShowAllResturantsInDistrict()
{
    for (auto rest : resturants)
    {
        cout << rest->GetName() << " (" << name << ")" << endl;
    }
}

void District::ShowSomeResturantsInDistrict(string fn)
{
    for (auto rest : resturants)
    {
        if (rest->HaveFoodInMenu(fn))
        {
            cout << rest->GetName() << " (" << name << ")" << endl;
        }
    }
}

void District::SortResturantsVector()
{
    sort(resturants.begin(), resturants.end(),
         [](Resturant *left, Resturant *right)
         { return left->GetName() < right->GetName(); });
}

Resturant *District::FindRestaurant(string name)
{
    for (auto rest : resturants)
    {
        if (rest->GetName() == name)
        {
            return rest;
        }
    }
    return nullptr;
}
void District::ShowAllReserve(User *user)
{
    for (auto rest : resturants)
    {
        rest->ShowReserve(user);
    }
}
void District::ShowOneReserve(User *user, int res_id)
{
    for (auto rest : resturants)
    {
        rest->ShowReserve(user, res_id);
    }
}

User::User(string username_, string password_)
{
    username = username_;
    password = password_;

    district = nullptr;

    state = IN_APP;
}

bool User::CheckUsername(string username_)
{
    return username == username_;
}

bool User::CheckPassword(string password_)
{
    return password == password_;
}

void User::ChangeStateToLoggedOut()
{
    state = LOGGED_OUT;
}

void User::ChangeStateToInApp()
{
    state = IN_APP;
}

void User::SetDistrict(District *dist)
{
    district = dist;
}

District *User::GetDistrict()
{
    return district;
}