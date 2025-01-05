#include "UTaste.hpp"

UTaste::UTaste()
{
    user = nullptr;
}

void UTaste::GetDataFromResturantsFile(char argv[])
{
    ifstream ResturantsFile(argv);
    string line, word;
    getline(ResturantsFile, line);

    while (getline(ResturantsFile, line))
    {
        stringstream X(line);
        string word;
        string name, dist, menu;
        int op_t, cl_t, num;
        District *dist_ptr;

        for (int i = 1; getline(X, word, ','); i++)
        {
            if (i == 1)
            {
                name = word;
            }
            if (i == 2)
            {
                dist = word;

                for (auto ptr : districts)
                {
                    if (ptr->GetName() == dist)
                    {
                        dist_ptr = ptr;
                    }
                }
            }
            if (i == 3)
            {
                menu = word;
            }
            if (i == 4)
            {
                op_t = stoi(word);
            }
            if (i == 5)
            {
                cl_t = stoi(word);
            }
            if (i == 6)
            {
                num = stoi(word);
            }
        }
        dist_ptr->AddResturant(name, menu, op_t, cl_t, num);
    }

    for (auto dist : districts)
    {
        dist->SortResturantsVector();
        for (auto res_ : dist->GetRestaurants())
        {
            res_->SortMenuItemVector();
        }
    }

    ResturantsFile.close();
}

void UTaste::GetDataFromDistrictsFile(char argv[])
{
    ifstream DistrictFile(argv);
    string line, word;
    District *dist_ptr;
    getline(DistrictFile, line);

    while (getline(DistrictFile, line))
    {
        stringstream X(line);
        for (int i = 1; getline(X, word, ','); i++)
        {
            if (i == 1)
            {
                bool founded = true;
                for (auto nei : districts)
                {
                    if (nei->GetName() == word)
                    {
                        founded = false;
                        dist_ptr = nei;
                    }
                }
                if (founded)
                {
                    dist_ptr = new District(word);
                    districts.push_back(dist_ptr);
                }
            }
            if (i == 2)
            {
                stringstream Y(word);
                string neigh;
                for (int j = 1; getline(Y, neigh, ';'); j++)
                {
                    bool founded = true;
                    for (auto nei : districts)
                    {
                        if (nei->GetName() == neigh)
                        {
                            founded = false;
                            dist_ptr->AddNeighbors(nei);
                        }
                    }
                    if (founded)
                    {
                        District *new_dist = new District(neigh);
                        districts.push_back(new_dist);
                        dist_ptr->AddNeighbors(new_dist);
                    }
                }
            }
        }
    }
    sort(districts.begin(), districts.end(),
         [](District *left, District *right)
         { return (left->GetName() < right->GetName()); });

    DistrictFile.close();
}

void UTaste::GetDataFromDiscountsFile(char argv[])
{
    ifstream DiscountFile(argv);
    string line, word;
    Resturant *restuarant;
    District *dist_ptr;
    MenuItem *menu_item;
    getline(DiscountFile, line);
    while (getline(DiscountFile, line))
    {
        stringstream X(line);
        for (int i = 1; getline(X, word, ','); i++)
        {
            if (i == 1)
            {
                for (auto dis : districts)
                {
                    if (dis->FindRestaurant(word) != nullptr)
                    {
                        restuarant = dis->FindRestaurant(word);
                    }
                }
            }
            if (i == 2)
            {
                stringstream Y(word);
                string kalameh;
                string type;
                int discount;
                int minimum;
                bool is_discount = true;

                for (int j = 1; getline(Y, kalameh, ';'); j++)
                {
                    if (kalameh == "none")
                    {
                        is_discount = false;
                        break;
                    }

                    if (j == 1)
                    {
                        type = kalameh;
                    }
                    if (j == 2)
                    {
                        minimum = stoi(kalameh);
                    }
                    if (j == 3)
                    {
                        discount = stoi(kalameh);
                    }
                }
                if (is_discount)
                {
                    restuarant->AddTotalDiscount(type, minimum, discount);
                }
            }
            if (i == 3)
            {
                stringstream Y(word);
                string kalameh;
                string type;
                int discount;
                bool is_discount = true;

                for (int j = 1; getline(Y, kalameh, ';'); j++)
                {
                    if (kalameh == "none")
                    {
                        is_discount = false;
                        break;
                    }
                    if (j == 1)
                    {
                        type = kalameh;
                    }
                    if (j == 2)
                    {
                        discount = stoi(kalameh);
                    }
                }
                if (is_discount)
                {
                    restuarant->AddFirstOrderDiscount(type, discount);
                }
            }
            if (i == 4)
            {
                stringstream Y(word);
                string kalameh;
                string type;
                string food_name;
                int discount;
                bool is_discount = true;

                for (int j = 1; getline(Y, kalameh, '|'); j++)
                {
                    if (kalameh == "none")
                    {
                        is_discount = false;
                        break;
                    }
                    stringstream Z(kalameh);
                    string loghat;
                    for (int k = 1; getline(Z, loghat, ';'); k++)
                    {
                        if (k == 1)
                        {
                            type = loghat;
                        }
                        if (k == 2)
                        {
                            stringstream A(loghat);
                            string vazheh;
                            for (int l = 1; getline(A, vazheh, ':'); l++)
                            {
                                if (l == 1)
                                {
                                    food_name = vazheh;
                                    menu_item = restuarant->FindMenuItem(food_name);
                                }
                                if (l == 2)
                                {
                                    discount = stoi(vazheh);
                                }
                            }
                            if (is_discount)
                            {
                                menu_item->AddFoodDiscount(type, discount);
                            }
                            
                        }
                    }
                }
            }
        }
    }
}

void UTaste::CheckUserLogin()
{
    if (user == nullptr)
    {
        throw runtime_error(PERMISSION_DENIED);
    }
}

void UTaste::IoHandler()
{
    string line;
    vector<string> requests;

    while (getline(cin, line))
    {
        requests = StringSplitter(line);

        try
        {
            if (requests[0] == PUT)
            {
                CheckUserLogin();
                PUTHandler(requests);
            }
            else if (requests[0] == GET)
            {
                CheckUserLogin();
                GETHandler(requests);
            }
            else if (requests[0] == DELETE)
            {
                CheckUserLogin();
                DELETEHandler(requests);
            }
            else if (requests[0] == POST)
            {
                POSTHandler(requests);
            }
            else
            {
                throw runtime_error(BAD_REQUEST);
            }
        }
        catch (const std::invalid_argument &e)
        {
            cout << BAD_REQUEST << endl;
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }

        requests.clear();
        line.clear();
    }
}

void UTaste::POSTHandler(vector<string> requests)
{
    if (requests[1] == SIGN_UP)
    {
        SignUp(requests);
    }
    else if (requests[1] == LOG_IN)
    {
        LogIn(requests);
    }
    else if (requests[1] == LOG_OUT)
    {
        LogOut(requests);
    }
    else if (requests[1] == RESERVE)
    {
        CheckUserLogin();
        ReserveHandler(requests);
    }
    else if (requests[1] == INCREASE_BUDGET)
    {
        CheckUserLogin();
        IncreaseBudget(requests);
    }
    else
    {
        throw runtime_error(NOT_FOUND);
    }
}

void UTaste::SignUp(vector<string> requests)
{
    if (user != nullptr)
    {
        throw runtime_error(PERMISSION_DENIED);
    }

    for (auto user_ : app_users)
    {
        if (user_->CheckUsername(requests[5]))
        {
            throw runtime_error(BAD_REQUEST);
        }
    }

    if (requests[3] != USER_NAME || requests[5] != PASSWORD)
    {
        throw runtime_error(NOT_FOUND);
    }

    User *new_user = new User(requests[4], requests[6]);
    user = new_user;
    app_users.push_back(new_user);
    cout << "OK" << endl;
}

void UTaste::LogOut(vector<string> requests)
{
    if (user == nullptr)
    {
        throw runtime_error(PERMISSION_DENIED);
    }

    for (auto user_ : app_users)
    {
        if (user_ == user)
        {
            user_->ChangeStateToLoggedOut();
        }
    }
    user = nullptr;
    cout << OK << endl;
}

void UTaste::LogIn(vector<string> requests)
{
    if (user != nullptr)
    {
        throw runtime_error(PERMISSION_DENIED);
    }

    if (requests[3] != USER_NAME || requests[5] != PASSWORD)
    {
        throw runtime_error(NOT_FOUND);
    }

    for (auto user_ : app_users)
    {
        if (user_->CheckUsername(requests[4]))
        {
            if (user_->CheckPassword(requests[6]))
            {
                user = user_;
                user->ChangeStateToInApp();
                cout << OK << endl;
                return;
            }
            else
            {
                throw runtime_error(PERMISSION_DENIED);
            }
        }
    }

    throw runtime_error(NOT_FOUND);
}

void UTaste::ReserveHandler(vector<string> requests)
{
    Resturant *rest = nullptr;

    for (auto dist : districts)
    {
        if (dist->FindRestaurant(requests[4]) != nullptr)
        {
            rest = dist->FindRestaurant(requests[4]);
        }
    }
    if (rest == nullptr)
    {
        throw(NOT_FOUND);
    }

    rest->ReserveHandler(requests, user, rest);
}

void UTaste::IncreaseBudget(vector<string> requests)
{
    if (requests[3] != AMOUNT)
    {
        throw runtime_error(NOT_FOUND);
    }

    int b = stoi(requests[4]);

    if (b < 0)
    {
        throw runtime_error(BAD_REQUEST);
    }

    user->SetBudget(b);
}

void UTaste::PUTHandler(vector<string> requests)
{
    if (requests[1] == MY_DISTRICT)
    {
        SetUserDistrict(requests);
    }
    else
    {
        throw runtime_error(NOT_FOUND);
    }
}

void UTaste::SetUserDistrict(vector<string> requests)
{
    if (requests[3] != DISTRICT)
    {
        throw runtime_error(NOT_FOUND);
    }

    for (auto dist : districts)
    {
        if (dist->GetName() == requests[4])
        {
            user->SetDistrict(dist);
            cout << OK << endl;
            return;
        }
    }
    throw runtime_error(NOT_FOUND);
}

void UTaste::DELETEHandler(vector<string> requests)
{
    if (requests[1] == RESERVE)
    {
        DeleteReserve(requests);
    }
}

void UTaste::DeleteReserve(vector<string> requests)
{
    Resturant *rest = nullptr;

    for (auto dist : districts)
    {
        if (dist->FindRestaurant(requests[4]) != nullptr)
        {
            rest = dist->FindRestaurant(requests[4]);
        }
    }

    if (rest == nullptr)
    {
        throw runtime_error(NOT_FOUND);
    }

    rest->DeleteReserve(stoi(requests[6]), user);
}

void UTaste::GETHandler(vector<string> requests)
{
    if (requests[1] == DISTRICTS)
    {
        ShowDistrict(requests);
    }
    else if (requests[1] == RESTAURANTS)
    {
        ShowResturantsList(requests);
    }
    else if (requests[1] == RESERVE)
    {
        ShowReserve(requests);
    }
    else if (requests[1] == RESTAURANT_DETAIL)
    {
        ShowRestaurantInfo(requests);
    }
    else if (requests[1] == SHOW_BUDGET)
    {
        ShowBudget(requests);
    }
    else
    {
        throw runtime_error(NOT_FOUND);
    }
}

void UTaste::ShowDistrict(vector<string> requests)
{
    if (districts.empty())
    {
        throw runtime_error(EMPTY);
    }
    if (requests.size() == 3)
    {
        for (auto dist : districts)
        {
            if (!dist->CheckNeighbor())
            {
                dist->PrintDistrictInfo();
            }
        }
    }
    else
    {
        if (requests[3] != DISTRICT)
        {
            throw runtime_error(NOT_FOUND);
        }

        for (auto dist : districts)
        {
            if (dist->GetName() == requests[4])
            {
                dist->PrintDistrictInfo();
                return;
            }
        }
        throw runtime_error(NOT_FOUND);
    }
}

void UTaste::ShowResturantsList(vector<string> requests)
{
    if (districts.empty())
    {
        throw runtime_error(EMPTY);
    }
    if (user->GetDistrict() == nullptr)
    {
        throw runtime_error(NOT_FOUND);
    }

    District *user_dist = user->GetDistrict();

    queue<District *> q;
    set<District *> visited;

    q.push(user_dist);
    visited.insert(user_dist);

    while (!q.empty())
    {
        District *curr_dist = q.front();
        q.pop();

        if (requests.size() == 3)
        {
            curr_dist->ShowAllResturantsInDistrict();
        }
        else
        {
            curr_dist->ShowSomeResturantsInDistrict(requests[4]);
        }

        for (auto nei : curr_dist->GetNeighbor())
        {
            if (visited.find(nei) == visited.end())
            {
                q.push(nei);
                visited.insert(nei);
            }
        }
    }
}

void UTaste::ShowReserve(vector<string> requests)
{
    if (requests.size() == 3)
    {
        for (auto dist : districts)
        {
            dist->ShowAllReserve(user);
        }
    }
    if (requests.size() == 5)
    {
        for (auto dist : districts)
        {
            if (dist->FindRestaurant(requests[4]) != nullptr)
            {
                dist->ShowAllReserve(user);
            }
        }
    }
    if (requests.size() == 7)
    {
        for (auto dist : districts)
        {
            if (dist->FindRestaurant(requests[4]) != nullptr)
            {
                dist->ShowOneReserve(user, stoi(requests[6]));
            }
        }
    }
}

void UTaste::ShowRestaurantInfo(vector<string> requests)
{
    District *curr;
    Resturant *curr_rest = nullptr;
    for (auto dist : districts)
    {
        if (dist->FindRestaurant(requests[4]) != nullptr)
        {
            curr_rest = dist->FindRestaurant(requests[4]);
            curr = dist;
        }
    }
    if (curr_rest == nullptr)
    {
        throw runtime_error(NOT_FOUND);
    }
    curr_rest->ShowRestaurantInfo(curr);
}

void UTaste::ShowBudget(vector<string> requests)
{
    cout << user->GetBudget() << endl;
}
