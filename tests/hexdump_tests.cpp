#include "cpp-utils/hexdump.hpp"
#include <gmock/gmock.h>

#include <numeric>
#include <sstream>

TEST(HexDump, WithAscii)
{
    std::string output = "0x000000: 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f  ................\n"
                         "0x000010: 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f  ................\n"
                         "0x000020: 20 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f   !\"#$%&'()*+,-./\n"
                         "0x000030: 30 31 32 33 34 35 36 37 38 39 3a 3b 3c 3d 3e 3f  0123456789:;<=>?\n"
                         "0x000040: 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f  @ABCDEFGHIJKLMNO\n"
                         "0x000050: 50 51 52 53 54 55 56 57 58 59 5a 5b 5c 5d 5e 5f  PQRSTUVWXYZ[\\]^_\n"
                         "0x000060: 60 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f  `abcdefghijklmno\n"
                         "0x000070: 70 71 72 73 74 75 76 77 78 79 7a 7b 7c 7d 7e 7f  pqrstuvwxyz{|}~.\n"
                         "0x000080: 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f  ................\n"
                         "0x000090: 90 91 92 93 94 95                                ......";

    std::vector<unsigned char> data(150);
    std::iota(data.begin(), data.end(), 0);

    std::stringstream ss;
    ss << cu::Hexdump(&data.at(0), data.size());
    EXPECT_EQ(ss.str(), output);
}

TEST(HexDump, CustomRowSizeWithoutAscii)
{
    std::string output = "0x000000: 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 20 21 22 23 24 25 26 27  \n"
                         "0x000028: 28 29 2a 2b 2c 2d 2e 2f 30 31 32 33 34 35 36 37 38 39 3a 3b 3c 3d 3e 3f 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f  \n"
                         "0x000050: 50 51 52 53 54 55 56 57 58 59 5a 5b 5c 5d 5e 5f 60 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f 70 71 72 73 74 75 76 77  \n"
                         "0x000078: 78 79 7a 7b 7c 7d 7e 7f 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f 90 91 92 93 94 95                                ";

    std::vector<unsigned char> data(150);
    std::iota(data.begin(), data.end(), 0);

    std::stringstream ss;
    ss << cu::CustomHexdump<40, false>(&data.at(0), data.size());
    EXPECT_EQ(ss.str(), output);
}