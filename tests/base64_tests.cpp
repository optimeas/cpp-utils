// changes by MAK: added namespace cu; removed console output; added ASSERT_EQ for rest*_reference; added RFC 4648 test vectors

#include "cpp-utils/base64.hpp"
#include <iostream>

#include <gtest/gtest.h>

TEST(Base64, encode)
{
   const std::string s =
       "René Nyffenegger\n"
       "http://www.renenyffenegger.ch\n"
       "passion for data\n";

   std::string encoded = cu::base64_encode(reinterpret_cast<const unsigned char *>(s.c_str()), s.length());
   std::string decoded = cu::base64_decode(encoded);

   ASSERT_EQ(decoded, s);

   // Test all possibilites of fill bytes (none, one =, two ==)
   // References calculated with: https://www.base64encode.org/

   std::string rest0_original = "abc";
   std::string rest0_reference = "YWJj";

   std::string rest0_encoded = cu::base64_encode(reinterpret_cast<const unsigned char *>(rest0_original.c_str()),
                                             rest0_original.length());
   std::string rest0_decoded = cu::base64_decode(rest0_encoded);

   ASSERT_EQ(rest0_encoded, rest0_reference);
   ASSERT_EQ(rest0_decoded, rest0_original);

   std::string rest1_original = "abcd";
   std::string rest1_reference = "YWJjZA==";

   std::string rest1_encoded = cu::base64_encode(reinterpret_cast<const unsigned char *>(rest1_original.c_str()),
                                             rest1_original.length());
   std::string rest1_decoded = cu::base64_decode(rest1_encoded);

   ASSERT_EQ(rest1_encoded, rest1_reference);
   ASSERT_EQ(rest1_decoded, rest1_original);

   std::string rest2_original = "abcde";
   std::string rest2_reference = "YWJjZGU=";

   std::string rest2_encoded = cu::base64_encode(reinterpret_cast<const unsigned char *>(rest2_original.c_str()),
                                             rest2_original.length());
   std::string rest2_decoded = cu::base64_decode(rest2_encoded);

   ASSERT_EQ(rest2_encoded, rest2_reference);
   ASSERT_EQ(rest2_decoded, rest2_original);

   // RFC 4648 specifies these test vectors:
   ASSERT_EQ(cu::base64_encode(std::string("")),       "");
   ASSERT_EQ(cu::base64_encode(std::string("f")),      "Zg==");
   ASSERT_EQ(cu::base64_encode(std::string("fo")),     "Zm8=");
   ASSERT_EQ(cu::base64_encode(std::string("foo")),    "Zm9v");
   ASSERT_EQ(cu::base64_encode(std::string("foob")),   "Zm9vYg==");
   ASSERT_EQ(cu::base64_encode(std::string("fooba")),  "Zm9vYmE=");
   ASSERT_EQ(cu::base64_encode(std::string("foobar")), "Zm9vYmFy");
}
