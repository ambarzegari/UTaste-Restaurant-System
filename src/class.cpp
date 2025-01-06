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
void Reserve::SetDiscount(int original, int first_order, int total_item, int total_price)
{
    original_price = original;
    first_order_dis = first_order;
    total_item_dis = total_item;
    total_price_dis = total_price;
}

MenuItem::MenuItem(string n, int p)
{
    name = n;
    price = p;
    food_discount = nullptr;
}

string MenuItem::GetName()
{
    return name;
}

int MenuItem::Getprice()
{
    return price;
}

void MenuItem::AddFoodDiscount(string t_, int dis_)
{
    food_discount = new FoodDiscount(t_, dis_);
}

Resturant::Resturant(string n, string menu, int op, int cl, int num)
{
    name = n;
    opening_time = op;
    closing_time = cl;
    number_of_tables = num;
    Reserve_num = 0;

    first_order_discount = nullptr;
    total_price_discount = nullptr;

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
                ((res->GetEndTime() <= et) && (res->GetStartTime() >= st)) ||
                ((st < opening_time) && (et > closing_time)))
            {
                throw runtime_error(PERMISSION_DENIED);
            }
        }
    }
    if (st < opening_time || et > closing_time)
    {
        throw runtime_error(PERMISSION_DENIED);
    }

    int original_price = 0;
    int total_item_specific_discount = 0;
    int first_order_dis = 0;
    int order_dis = 0;
    for (auto food : f)
    {
        original_price += food->Getprice();
        if (food->GetFoodDiscount() != nullptr)
        {
            total_item_specific_discount += food->GetFoodDiscount()->CalculateDiscount(food->Getprice());
        }
    }
    bool is_first_order = true;
    for (auto res : reserve)
    {
        if (res->GetUser() == us)
        {
            is_first_order = false;
        }
    }
    if (is_first_order)
    {
        if (first_order_discount != nullptr)
        {
            first_order_dis = first_order_discount->CalculateDiscount(original_price - total_item_specific_discount);
        }
    }
    if (total_price_discount != nullptr)
    {
        if (original_price - first_order_dis - total_item_specific_discount > total_price_discount->GetMinimum())
        {
            order_dis = total_price_discount->CalculateDiscount(original_price - first_order_dis - total_item_specific_discount);
        }
    }
    int total_dis = order_dis + first_order_dis + total_item_specific_discount;

    us->ReduceBudget(original_price - total_dis);

    Reserve_num++;
    reserve.push_back(new Reserve(res, us, st, et, tid, Reserve_num, f));
    cout << "Table " << tid << " for " << st << " to " << et << " in " << name << endl;

    reserve[reserve.size() - 1]->SetDiscount(original_price, first_order_dis, total_item_specific_discount, order_dis);

    cout << "Original Price: " << original_price << endl;

    cout << "Order Amount Discount: " << order_dis << endl;

    cout << "Total Item Specific: " << total_item_specific_discount << endl;

    cout << "First Order Discount: " << first_order_dis << endl;

    cout << "Toatal Discount: " << total_dis << endl;

    cout << "Total Price: " << original_price - total_dis << endl;
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

    if (stoi(requests[6]) > number_of_tables)
    {
        throw runtime_error(NOT_FOUND);
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
    if (total_price_discount != nullptr)
    {
        if (total_price_discount->GetType() == "percent")
        {
            cout << "Order Amount Discount: " << "percentage, " << total_price_discount->GetMinimum() << ", " << total_price_discount->GetDiscount() << endl;
        }
        if (total_price_discount->GetType() == "amount")
        {
            cout << "Order Amount Discount: " << "amount, " << total_price_discount->GetMinimum() << ", " << total_price_discount->GetDiscount() << endl;
        }
    }

    int l = 1;
    int k = 1;
    for (auto menu : menu_item)
    {
        if (menu->GetFoodDiscount() != nullptr)
        {
            if (l == 1)
            {
                cout << "Item Specific Discount: ";
                l++;
            }

            if (k != 1)
            {
                cout << ", ";
            }
            if (menu->GetFoodDiscount()->GetType() == "percent")
            {
                cout << menu->GetName() << "(" << "percentage: " << menu->GetFoodDiscount()->GetDiscount() << ")";
            }
            if (menu->GetFoodDiscount()->GetType() == "amount")
            {
                cout << menu->GetName() << "(" << "amount: " << menu->GetFoodDiscount()->GetDiscount() << ")";
            }
            k++;
        }
    }
    if (l == 2)
    {
        cout << endl;
    }

    if (first_order_discount != nullptr)
    {
        if (first_order_discount->GetType() == "percent")
        {
            cout << "First Order Discount: " << "percentage, " << first_order_discount->GetDiscount() << endl;
        }
        if (first_order_discount->GetType() == "amount")
        {
            cout << "First Order Discount: " << "amount, " << first_order_discount->GetDiscount() << endl;
        }
    }
}

void Resturant::AddTotalDiscount(string t_, int min_, int dis_)
{
    total_price_discount = new TotalPriceDiscount(t_, min_, dis_);
}

void Resturant::AddFirstOrderDiscount(string t_, int dis_)
{
    first_order_discount = new FirstOrderDiscount(t_, dis_);
}

MenuItem *Resturant::FindMenuItem(string n_)
{
    for (auto item : menu_item)
    {
        if (item->GetName() == n_)
        {
            return item;
        }
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

    budget = 0;
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

void User::SetBudget(int b)
{
    budget = budget + b;
    cout << OK << endl;
}

int User::GetBudget()
{
    return budget;
}

void User::ReduceBudget(int n)
{
    if (n > budget)
    {
        throw runtime_error(PERMISSION_DENIED);
    }

    budget -= n;
}

Discount::Discount(string t_, int dis_)
{
    type = t_;
    discount = dis_;
}

TotalPriceDiscount::TotalPriceDiscount(string t_, int min_, int dis_) : Discount(t_, dis_)
{
    minimum = min_;
}

int Discount::CalculateDiscount(int price)
{
    if (type == "percent")
    {
        return (price * discount / 100);
    }
    else if (type == "amount")
    {
        return discount;
    }
}

FirstOrderDiscount::FirstOrderDiscount(string t_, int dis_) : Discount(t_, dis_)
{
}

FoodDiscount::FoodDiscount(string t_, int dis_) : Discount(t_, dis_)
{
}