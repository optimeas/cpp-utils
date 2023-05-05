#include "cpp-utils/timeutils.hpp"

#include <chrono>
#include <sstream>
#include <iomanip>

namespace cu
{

std::string getCurrentTimestampUtcIso8601()
{
    auto now = std::chrono::system_clock::now();
    auto itt = std::chrono::system_clock::to_time_t(now);
    std::ostringstream ss;
    struct tm result;
    ss << std::put_time(gmtime_r(&itt, &result), "%FT%TZ");
    return  ss.str();
}

}
