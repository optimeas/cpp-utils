#include "cpp-utils/timedthresholdcounter.hpp"

#include <iostream>

namespace cu
{

TimedThresholdCounter::TimedThresholdCounter()
{

}

void TimedThresholdCounter::enable()
{
    m_enabled = true;
}

void TimedThresholdCounter::disable()
{
    m_enabled = false;
}

void TimedThresholdCounter::increment()
{
    if(!m_enabled)
        return;

    m_bouncing = false;
    auto now = std::chrono::steady_clock::now();

    if(std::chrono::duration_cast<std::chrono::milliseconds>(m_timePointLastIncrement.time_since_epoch()).count() > 0)
    {
        if(((now - m_timePointLastIncrement) < m_debounceTime))
        {
            m_bouncing = true;
            return;
        }
    }

    if((m_thresholdTimeWindow.count() > 0) && ((now - m_timePointLastIncrement) > m_thresholdTimeWindow))
        m_counter = 0;

    m_counter++;
    m_timePointLastIncrement = now;
}

void TimedThresholdCounter::clear()
{
    m_counter = 0;
    m_bouncing = false;
}

bool TimedThresholdCounter::isBouncing()
{
    return m_bouncing;
}

bool TimedThresholdCounter::isThresholdExceeded()
{
    return (m_counter > m_threshold);
}

const std::chrono::duration<double> &TimedThresholdCounter::debounceTime() const
{
    return m_debounceTime;
}

void TimedThresholdCounter::setDebounceTime(const std::chrono::duration<double> &newDebounceTime)
{
    m_debounceTime = newDebounceTime;
}

const std::chrono::duration<double> &TimedThresholdCounter::thresholdTimeWindow() const
{
    return m_thresholdTimeWindow;
}

void TimedThresholdCounter::setThresholdTimeWindow(const std::chrono::duration<double> &newThresholdTimeWindow)
{
    m_thresholdTimeWindow = newThresholdTimeWindow;
}

bool TimedThresholdCounter::isEnabled() const
{
    return m_enabled;
}

uint32_t TimedThresholdCounter::value() const
{
    return m_counter;
}

uint32_t TimedThresholdCounter::threshold() const
{
    return m_threshold;
}

void TimedThresholdCounter::setThreshold(uint32_t newThreshold)
{
    m_threshold = newThreshold;
}

}
