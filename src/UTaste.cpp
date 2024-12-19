#include "UTaste.hpp"

UTaste::UTaste()
{
    user = nullptr;
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
            }
            else if (requests[0] == GET)
            {
            }
            else if (requests[0] == DELETE)
            {
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
        catch (const exception &e)
        {
            cerr << e.what() << endl;
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

    requests[4].erase(requests[4].begin());
    requests[4].erase(requests[4].end());
    requests[6].erase(requests[6].begin());
    requests[6].erase(requests[6].end());

    User *new_user = new User(requests[4], requests[6]);

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

    requests[4].erase(requests[4].begin());
    requests[4].erase(requests[4].end());
    requests[6].erase(requests[6].begin());
    requests[6].erase(requests[6].end());

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

void UTaste::PUTHandler(vector<string> requests)
{
}
void UTaste::DELETEHandler(vector<string> requests)
{
}
void UTaste::GETHandler(vector<string> requests)
{
}