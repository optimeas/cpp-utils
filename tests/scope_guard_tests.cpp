#include "cpp-utils/scope_guard.hpp"
#include <gmock/gmock.h>


TEST(ScopeGuard, ExitWithoutException)
{
    int called = false;
    {
        CU_SCOPE_EXIT{called = true;};
    }
    EXPECT_TRUE(called);
}

TEST(ScopeGuard, ExitWithException)
{
    int called = false;

    try
    {
        CU_SCOPE_EXIT{called = true;};
        throw std::runtime_error("some exception");
        FAIL() << "Expected std::runtime_error"; // cppcheck-suppress unreachableCode
    }
    catch(std::runtime_error const &err)
    {
        EXPECT_EQ(err.what(), std::string("some exception"));
    }
    catch(...)
    {
        FAIL() << "Expected std::runtime_error";
    }

    EXPECT_TRUE(called);
}

TEST(ScopeGuard, FailWithoutException)
{
    int called = false;
    {
        CU_SCOPE_FAIL{called = true;};
    }
    EXPECT_FALSE(called);
}

TEST(ScopeGuard, FailWithException)
{
    int called = false;

    try
    {
        CU_SCOPE_FAIL{called = true;};
        throw std::runtime_error("some exception");
        FAIL() << "Expected std::runtime_error"; // cppcheck-suppress unreachableCode
    }
    catch(std::runtime_error const &err)
    {
        EXPECT_EQ(err.what(), std::string("some exception"));
    }
    catch(...)
    {
        FAIL() << "Expected std::runtime_error";
    }

    EXPECT_TRUE(called);
}

TEST(ScopeGuard, SuccessWithoutException)
{
    int called = false;
    {
        CU_SCOPE_SUCCESS{called = true;};
    }
    EXPECT_TRUE(called);
}

TEST(ScopeGuard, SuccessWithException)
{
    int called = false;

    try
    {
        CU_SCOPE_SUCCESS{called = true;};
        throw std::runtime_error("some exception");
        FAIL() << "Expected std::runtime_error"; // cppcheck-suppress unreachableCode
    }
    catch(std::runtime_error const &err)
    {
        EXPECT_EQ(err.what(), std::string("some exception"));
    }
    catch(...)
    {
        FAIL() << "Expected std::runtime_error";
    }

    EXPECT_FALSE(called);
}
