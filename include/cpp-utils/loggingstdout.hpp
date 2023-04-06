#pragma once

#include "cpp-utils/logging.hpp"

namespace cu
{

class StandardOutputLogger : public LoggingInterface
{
private:
    virtual void writeMessage(LoggingLevel level, std::string_view entry, const source_location &location) override;
};

class NullLogger : public LoggingInterface
{
private:
    virtual void writeMessage(LoggingLevel level, std::string_view entry, const source_location &location) override;
};

}
