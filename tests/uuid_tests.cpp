// changes by MAK: renamed namespace sole into cu

#include "cpp-utils/uuid.hpp"

#include <gtest/gtest.h>
#include <iostream>

TEST(Uuid, demo)
{
    cu::uuid u0 = cu::uuid0(), u1 = cu::uuid1(), u4 = cu::uuid4();

    std::cout << "uuid v0 string : " << u0 << std::endl;
    std::cout << "uuid v0 base62 : " << u0.base62() << std::endl;
    std::cout << "uuid v0 pretty : " << u0.pretty() << std::endl << std::endl;

    std::cout << "uuid v1 string : " << u1 << std::endl;
    std::cout << "uuid v1 base62 : " << u1.base62() << std::endl;
    std::cout << "uuid v1 pretty : " << u1.pretty() << std::endl << std::endl;

    std::cout << "uuid v4 string : " << u4 << std::endl;
    std::cout << "uuid v4 base62 : " << u4.base62() << std::endl;
    std::cout << "uuid v4 pretty : " << u4.pretty() << std::endl << std::endl;

    u1 = cu::rebuild("F81D4FAE-7DEC-11D0-A765-00A0C91E6BF6");
    u4 = cu::rebuild("GITheR4tLlg-BagIW20DGja");

    std::cout << "uuid v1 rebuilt : " << u1 << " -> " << u1.pretty() << std::endl;
    std::cout << "uuid v4 rebuilt : " << u4 << " -> " << u4.pretty() << std::endl;
}
