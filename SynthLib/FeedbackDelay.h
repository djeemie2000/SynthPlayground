#pragma once

#include "DelayLine.h"

template<class T, class U = T>
class CFeedbackDelay
{
public:
    CFeedbackDelay(int Capacity, T DefaultValue)
        : m_DelayLine(Capacity, DefaultValue)
        , m_PrevValue(0)
        , m_Wet(0)
        , m_Feedback(0)
    {}

    void SetDelay(int Delay)
    {
        m_DelayLine.SetDelay(Delay);
    }

    void SetWet(U Wet)
    {
        m_Wet = Wet;
    }

    void SetFeedback(U Feedback)
    {
        m_Feedback = Feedback;
    }

    T operator()(T In)
    {
        // use feedback. Therefore a the previous output value from the delay line is remembered.
        // Feedback parameter determines the mix between the previous delay line output and the current input,
        // which is fed into the delay line
        // output signal is a mix of wet (delay line output) and dry signal (In)
        T InputValue = (1-m_Feedback)*In + m_Feedback*m_PrevValue;
        m_PrevValue = m_DelayLine(InputValue);
        return m_Wet*m_PrevValue + (1-m_Wet)*In;
    }

private:
    CDelayLine<T> m_DelayLine;
    T m_PrevValue;
    U m_Wet;
    U m_Feedback;
};
