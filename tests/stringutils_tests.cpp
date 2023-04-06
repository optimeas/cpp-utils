#include "cpp-utils/stringutils.hpp"
#include <gmock/gmock.h>

TEST(StringUtils, ltrim)
{
    std::string input = " \t\n\r\f\v Hello world \t\n\r\f\v ";
    std::string output = "Hello world \t\n\r\f\v ";

    cu::ltrim(input);
    EXPECT_EQ(input, output);

    EXPECT_EQ(cu::ltrim_copy(input), output);
}

TEST(StringUtils, rtrim)
{
    std::string input = " \t\n\r\f\v Hello world \t\n\r\f\v ";
    std::string output = " \t\n\r\f\v Hello world";

    cu::rtrim(input);
    EXPECT_EQ(input, output);

    EXPECT_EQ(cu::rtrim_copy(input), output);
}

TEST(StringUtils, trim)
{
    std::string input = " \t\n\r\f\v Hello world \t\n\r\f\v ";
    std::string output = "Hello world";

    cu::trim(input);
    EXPECT_EQ(input, output);

    EXPECT_EQ(cu::trim_copy(input), output);
}

TEST(StringUtils, simpleCase)
{
    EXPECT_EQ(cu::simpleCase("hello world"),  "Hello World");
    EXPECT_EQ(cu::simpleCase(" hello world"), " Hello World");
    EXPECT_EQ(cu::simpleCase("Hello world"),  "Hello World");
    EXPECT_EQ(cu::simpleCase("content-type"), "Content-Type");
}
