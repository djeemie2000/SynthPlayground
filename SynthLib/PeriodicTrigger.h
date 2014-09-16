#ifndef PERIODICTRIGGER_H
#define PERIODICTRIGGER_H

#include <cmath>

template<class T>
class CPeriodicTrigger
{
public:
    CPeriodicTrigger(T SamplingFrequency)
        : m_SamplingFrequency(SamplingFrequency)
        , m_Counter(0)
    {}

    void Sync()
    {
        m_Counter = 0;
    }

    T operator()(T Frequency)
    {
        T Period = m_SamplingFrequency/Frequency;
        m_Counter += 1;
        if(Period<=m_Counter)
        {
            m_Counter = std::fmod(m_SamplingFrequency, Frequency)/Frequency;//avoid rounding errors
            return 1.0f;
        }
        return 0.0f;
    }

private:
    T m_SamplingFrequency;
    T m_Counter;
};

#endif // PERIODICTRIGGER_H
