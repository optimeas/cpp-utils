#include "cpp-utils/timedthresholdcounter.hpp"
#include <gmock/gmock.h>

#include <thread>
#include <iostream>

TEST(TimedThresholdCounter, InitialState)
{
    cu::TimedThresholdCounter counter;

    EXPECT_TRUE(counter.isEnabled());
    EXPECT_FALSE(counter.isBouncing());
    EXPECT_FALSE(counter.isThresholdExceeded());
    EXPECT_EQ(counter.value(), 0);
}

TEST(TimedThresholdCounter, PlainCounter)
{
    cu::TimedThresholdCounter counter;
    counter.setThreshold(2);

    EXPECT_TRUE(counter.isEnabled());
    EXPECT_FALSE(counter.isBouncing());
    EXPECT_FALSE(counter.isThresholdExceeded());
    EXPECT_EQ(counter.value(), 0);

    counter.increment();
    counter.increment();

    EXPECT_FALSE(counter.isBouncing());
    EXPECT_FALSE(counter.isThresholdExceeded());
    EXPECT_EQ(counter.value(), 2);
}

TEST(TimedThresholdCounter, ThresholdExceeded)
{
    cu::TimedThresholdCounter counter;
    counter.setThreshold(2);

    EXPECT_TRUE(counter.isEnabled());
    EXPECT_FALSE(counter.isBouncing());
    EXPECT_FALSE(counter.isThresholdExceeded());
    EXPECT_EQ(counter.value(), 0);

    counter.increment();
    counter.increment();
    counter.increment();

    EXPECT_FALSE(counter.isBouncing());
    EXPECT_TRUE(counter.isThresholdExceeded());
    EXPECT_EQ(counter.value(), 3);
}

TEST(TimedThresholdCounter, WithTimeWindow)
{
    cu::TimedThresholdCounter counter;
    counter.setThreshold(2);
    counter.setThresholdTimeWindow(std::chrono::milliseconds(100));


    EXPECT_TRUE(counter.isEnabled());
    EXPECT_FALSE(counter.isBouncing());
    EXPECT_FALSE(counter.isThresholdExceeded());
    EXPECT_EQ(counter.value(), 0);

    counter.increment();
    counter.increment();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    counter.increment();

    EXPECT_FALSE(counter.isBouncing());
    EXPECT_FALSE(counter.isThresholdExceeded());
    EXPECT_EQ(counter.value(), 1);
}

TEST(TimedThresholdCounter, Bouncing)
{
    cu::TimedThresholdCounter counter;
    counter.setThreshold(2);
    counter.setDebounceTime(std::chrono::milliseconds(100));


    EXPECT_TRUE(counter.isEnabled());
    EXPECT_FALSE(counter.isBouncing());
    EXPECT_FALSE(counter.isThresholdExceeded());
    EXPECT_EQ(counter.value(), 0);

    counter.increment();
    counter.increment();
    EXPECT_TRUE(counter.isBouncing());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    counter.increment();
    EXPECT_FALSE(counter.isBouncing());

    EXPECT_TRUE(counter.isThresholdExceeded());
    EXPECT_EQ(counter.value(), 3);
}
