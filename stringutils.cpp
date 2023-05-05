#include "cpp-utils/stringutils.hpp"

namespace cu
{

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
