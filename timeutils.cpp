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

std::string getCurrentTimestampUtcString(bool withMilliSeconds)
{
    auto now = std::chrono::system_clock::now();
    auto itt = std::chrono::system_clock::to_time_t(now);
    auto fine = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    std::ostringstream ss;
    struct tm result;
    ss << std::put_time(gmtime_r(&itt, &result), "%Y%m%d_%H%M%S");

    if(withMilliSeconds)
        ss << std::setw(3) << std::setfill('0') << fine.time_since_epoch().count() % 1000;

    return  ss.str();
}

}
