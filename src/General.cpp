#include "General.hpp"

vector<string> StringSplitter(string line)
{
    stringstream s(line);
    string word;

    vector<string> words;

    while (s >> word)
    {
        words.push_back(word);
    }

    return words;
}

