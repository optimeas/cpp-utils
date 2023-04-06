#pragma once

#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>

namespace cu
{

// https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring/217605#217605
// trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s)
{
    trim(s);
    return s;
}


//std::string simpleCase(const std::string& text)
std::string simpleCase(std::string_view text)
{
    std::stringstream result;
    bool newwrd = true;

    for(const auto ch : text)
    {
        newwrd = newwrd || std::isspace(ch) || (ch == '-');
        if (std::isalpha(ch))
            if(newwrd)
            {
                result << static_cast<char>(std::toupper(ch));
                newwrd = false;
            }
            else
                result << static_cast<char>(std::tolower(ch));
        else
            result << ch;
    }

    return result.str();
}

}
