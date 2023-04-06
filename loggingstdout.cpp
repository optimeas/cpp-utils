#include "cpp-utils/loggingstdout.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <thread>
#include <iostream>

namespace cu
{

void StandardOutputLogger::writeMessage(LoggingLevel level, std::string_view entry, const source_location &location)
{
    std::string levelText;
    switch(level)
    {
    case LoggingLevel::ERROR:
        levelText = "ERROR  |";
        break;
    case LoggingLevel::WARNING:
        levelText = "WARNING|";
        break;
    case LoggingLevel::INFO:
        levelText = "INFO   |";
        break;
    case LoggingLevel::DEBUG:
        levelText = "DEBUG  |";
        break;
    }

    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto timer = std::chrono::system_clock::to_time_t(now);
    struct tm buffer;
    std::tm bt = *localtime_r(&timer, &buffer);
    std::ostringstream timestampStream;
    timestampStream << std::put_time(&bt, "%d.%m.%y|%H:%M:%S");
    timestampStream << '.' << std::setfill('0') << std::setw(3) << ms.count() << '|' ;

    std::string locationString;
    locationString.reserve(31);
    locationString= std::filesystem::path(location.file_name()).stem();
    locationString += ":" + std::to_string(location.line());
    locationString.resize(30, ' ');
    locationString += "|";

    std::cout << timestampStream.str() << std::this_thread::get_id() << "|" << locationString << levelText << entry << std::endl;
}

void NullLogger::writeMessage([[maybe_unused]] LoggingLevel level, [[maybe_unused]] std::string_view entry, [[maybe_unused]] const source_location &location)
{

}

}
