#include "Utaste.hpp"

Utaste::Utaste()
{
}

void Utaste::IoHandler()
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
            }
            else
            {
                throw runtime_error(BAD_REQUEST);
            }
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }
}