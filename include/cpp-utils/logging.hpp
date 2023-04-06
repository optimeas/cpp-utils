#pragma once

#if __has_include(<version>) // for __cpp_lib_source_location in C++20
    #include <version>
#endif

#if defined(__cpp_lib_source_location)
    #include <source_location>
    using source_location = std::source_location;
#else
    #include <experimental/source_location>
    using source_location = std::experimental::source_location;
#endif

#include <memory>
#include <string_view>

namespace cu
{

enum class LoggingLevel
{
    ERROR,
    WARNING,
    INFO,
    DEBUG
};

class LoggingInterface
{
public:
    virtual ~LoggingInterface() = default; // Prevent undefined behavior when used as base class and delete per base class pointer

    void error  (std::string_view entry, const source_location &location = source_location::current());
    void warning(std::string_view entry, const source_location &location = source_location::current());
    void info   (std::string_view entry, const source_location &location = source_location::current());
    void debug  (std::string_view entry, const source_location &location = source_location::current());

private:
    virtual void writeMessage(LoggingLevel level, std::string_view entry, const source_location &location) = 0;

};

using Logger = std::shared_ptr<LoggingInterface>;

}
