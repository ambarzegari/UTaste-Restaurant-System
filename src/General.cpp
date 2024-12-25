#include "General.hpp"

vector<string> StringSplitter(string input)
{
    string current_word;

    vector<string> words;

    bool inside_quotes = false;

    for (char ch : input)
    {
        if (ch == '"')
        {
            if (inside_quotes)
            {
                words.push_back(current_word);
                current_word.clear();
            }
            inside_quotes = !inside_quotes;
        }
        else if (inside_quotes)
        {
            current_word += ch;
        }
        else if (ch == ' ')
        {
            if (!current_word.empty())
            {
                words.push_back(current_word);
                current_word.clear();
            }
        }
        else
        {
            current_word += ch;
        }
    }

    if (!current_word.empty())
    {
        words.push_back(current_word);
    }

    return words;
}
