#pragma once

#include "DelayLine.h"

template<class T, class U = T>
class CFeedbackDelay
{
public:
    CFeedbackDelay(int Capacity, T DefaultValue)
        : m_Active(true)
        , m_DelayLine(Capacity, DefaultValue)
        , m_PrevIn(DefaultValue)
        , m_PrevDelayLineOutput(DefaultValue)
        , m_Wet(0)
        , m_Feedback(0)
    {}

    void SetBypass(bool Bypass)
    {
        m_Active = !Bypass;
    }

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
                    //T InputValue = (1-m_Feedback)*In + m_Feedback*m_PrevValue;

        if(m_Active)
        {
            T InputValue = m_PrevIn + m_Feedback*m_PrevDelayLineOutput;
            m_PrevDelayLineOutput = m_DelayLine(InputValue);
            m_PrevIn = In;
            return m_Wet*m_PrevDelayLineOutput + (1-m_Wet)*In;
        }
        return In;
    }

private:
    bool m_Active;
    CDelayLine<T> m_DelayLine;
    T m_PrevIn;
    T m_PrevDelayLineOutput;
    U m_Wet;
    U m_Feedback;
};
