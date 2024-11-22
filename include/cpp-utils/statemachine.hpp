#pragma once

#include <cstdint>

namespace cu {

template <typename T>
class StateMachine
{
public:
    explicit StateMachine(T initState)
        : m_current(initState)
        , m_next(initState)
    { }

    virtual ~StateMachine() = default;

    T currentState() const
    { return m_current; }

    uint32_t stateDuration() const
    { return m_stateDuration; }

    void    extendTimeOut(uint32_t t_timeOut_ticks)
    { if (m_timeOutActive)
        m_tTimeOut += t_timeOut_ticks; }

    uint32_t ticksToTimeout() const
    { return m_tTimeOut; }

    uint32_t ticksInDelay() const
    { return m_tDelay; }

    // to be called at each tick
    void    runTick()
    {
        handler();
        clock();
    }

protected:
    virtual void handler()
    {}

    virtual void notifyStateChanged()
    {}

    T nextState() const
    { return m_next; }

    void    transition(T transitTo)
    { m_next = transitTo; }
    bool    entering() const
    { return m_enteringState; }

    void    startTimeOut(uint32_t t_timeOut_ticks)
    { m_timeOutActive = true;
      m_tTimeOut = t_timeOut_ticks; }
    bool    isTimeOut()
    { if (m_tTimeOut || !m_timeOutActive)
        return false;
      m_timeOutActive = false;
      return true; }

    void    startDelay(uint32_t t_delay_ticks)
    { m_delayActive = true;
      m_tDelay = t_delay_ticks; }
    bool    endOfDelay()
    { if (m_tDelay || !m_delayActive)
        return false;
      m_delayActive = false;
      return true; }
    bool    delayEnded()
    { if (m_tDelay)
        return false;
      m_delayActive = false;
      return true; }

private:
    void clock()
    {
        m_enteringState = m_current != m_next;

        if (m_enteringState)
        {
            notifyStateChanged();
            m_stateDuration = 0;
            m_timeOutActive = false;
            m_tTimeOut	= 0;
            m_delayActive = false;
            m_tDelay	= 0;
        }
        else
        {
            if (m_stateDuration < UINT32_MAX)
                ++m_stateDuration;
            if (m_tTimeOut)
                --m_tTimeOut;
            if (m_tDelay)
                --m_tDelay;
        }

        m_current		= m_next;
    }

    bool        m_enteringState = true;
    uint32_t    m_stateDuration = 0;
    T           m_current = T{};
    T           m_next    = T{};

    bool        m_timeOutActive = false;
    uint32_t    m_tTimeOut = 0;

    bool        m_delayActive = false;
    uint32_t    m_tDelay   = 0;
};

} // namespace cu

