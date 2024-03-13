#include "cpp-utils/stringutils.hpp"
#include <gmock/gmock.h>

#include <iostream>

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

TEST(StringUtils, hexDecode)
{
    std::string hexString = "09e1c5f70a65ac519458e7e53f36";
    std::vector<unsigned char> expectVectorUnsignedChar {0x09, 0xe1, 0xc5, 0xf7, 0x0a, 0x65, 0xac, 0x51, 0x94, 0x58, 0xe7, 0xe5, 0x3f, 0x36};
    std::vector<std::byte> expectVectorStdByte {std::byte{0x09}, std::byte{0xe1}, std::byte{0xc5}, std::byte{0xf7}, std::byte{0x0a}, std::byte{0x65}, std::byte{0xac},
        std::byte{0x51}, std::byte{0x94}, std::byte{0x58}, std::byte{0xe7}, std::byte{0xe5}, std::byte{0x3f}, std::byte{0x36}};

    std::vector<unsigned char> vectorUnsignedChar = cu::hexDecode<unsigned char>(hexString);
    EXPECT_THAT(vectorUnsignedChar, testing::ElementsAreArray(expectVectorUnsignedChar.data(), expectVectorUnsignedChar.size()));

    std::vector<std::byte> vectorStdByte = cu::hexDecode<std::byte>(hexString);
    EXPECT_THAT(vectorStdByte, testing::ElementsAreArray(expectVectorStdByte.data(), expectVectorStdByte.size()));
}
