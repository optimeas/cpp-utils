#pragma once

#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>
#include <vector>
#include <fstream>

namespace cu
{

// https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring/217605#217605
// trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
    {
        return !(std::isspace(ch) || (ch == 0));
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
    {
        return !(std::isspace(ch) || (ch == 0));
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

std::string simpleCase(std::string_view text);

template<typename T>
std::vector<T> hexDecode(std::string_view hexString)
{
    std::vector<T> out;
    out.resize((hexString.length() +1)/ 2);

    T *result = static_cast<T *>(out.data() + out.size());

    bool odd_digit = true;
    for(int i = hexString.size() - 1; i >= 0; --i)
    {
        int ch = hexString.at(i);
        int tmp;
        if (ch >= '0' && ch <= '9')
            tmp = ch - '0';
        else if (ch >= 'a' && ch <= 'f')
            tmp = ch - 'a' + 10;
        else if (ch >= 'A' && ch <= 'F')
            tmp = ch - 'A' + 10;
        else
            continue;

        if(odd_digit)
        {
            --result;
            *result = static_cast<T>(tmp);
            odd_digit = false;
        }
        else
        {
            *result |= static_cast<T>(tmp << 4);
            odd_digit = true;
        }
    }

    unsigned char removeCount = result - static_cast<T *>(out.data());
    for(int i=0; i<removeCount; i++)
        out.erase(out.begin());

    return out;
}

std::string fileToString(const std::string &fullPath);

}
