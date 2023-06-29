#pragma once

#include <chrono>

namespace cu
{

class TimedThresholdCounter
{
public:
    TimedThresholdCounter();

    void enable();
    void disable();

    void increment();
    void clear();

    bool isBouncing();
    bool isThresholdExceeded();

    const std::chrono::duration<double> &debounceTime() const;
    void setDebounceTime(const std::chrono::duration<double> &newDebounceTime);

    const std::chrono::duration<double> &thresholdTimeWindow() const;
    void setThresholdTimeWindow(const std::chrono::duration<double> &newThresholdTimeWindow);

    bool isEnabled() const;

    uint32_t value() const;

    uint32_t threshold() const;
    void setThreshold(uint32_t newThreshold);

private:
    bool m_enabled{true};
    bool m_bouncing{false};
    uint32_t m_counter{0};
    std::chrono::time_point<std::chrono::steady_clock> m_timePointLastIncrement;
    std::chrono::duration<double> m_debounceTime{ };
    std::chrono::duration<double> m_thresholdTimeWindow{ };
    uint32_t m_threshold{0};
};

}
