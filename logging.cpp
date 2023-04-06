#include "cpp-utils/logging.hpp"
namespace cu
{

void LoggingInterface::error(std::string_view entry, const source_location &location)
{
    writeMessage(LoggingLevel::ERROR, entry, location);
}

void LoggingInterface::warning(std::string_view entry, const source_location &location)
{
    writeMessage(LoggingLevel::WARNING, entry, location);
}

void LoggingInterface::info(std::string_view entry, const source_location &location)
{
    writeMessage(LoggingLevel::INFO, entry, location);
}

void LoggingInterface::debug(std::string_view entry, const source_location &location)
{
    writeMessage(LoggingLevel::DEBUG, entry, location);
}


}
