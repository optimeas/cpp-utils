#include "cpp-utils/timeutils.hpp"

#include <chrono>
#include <sstream>
#include <iomanip>

namespace cu
{

std::string getCurrentTimestampUtcIso8601(bool withNanoSeconds)
{
    auto now = std::chrono::system_clock::now();
    auto itt = std::chrono::system_clock::to_time_t(now);
    auto fine = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    std::ostringstream ss;
    struct tm result;
    ss << std::put_time(gmtime_r(&itt, &result), "%FT%T");

    if(withNanoSeconds)
        ss << ","<< std::setw(9) << std::setfill('0') << fine.time_since_epoch().count() % 1000000000;

    ss << "Z";
    return  ss.str();
}

std::string getCurrentTimestampUtcFilename(bool withMilliSeconds)
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
