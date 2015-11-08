#pragma once

#include "DelayLine2.h"

template<class T>
class CCombFilter
{
public:
    CCombFilter(T SamplingFrequency)
     : m_SamplingFrequency(SamplingFrequency)
     , m_DelayLine(SamplingFrequency, 0)
    {
    }

    T operator()(T In, T Feedback, T Frequency)
    {
        // assumes Freq > 0
        T Delay = 0<Frequency ?  m_SamplingFrequency/Frequency : 0;
        Delay = Delay<m_DelayLine.GetCapacity() ? Delay : m_DelayLine.GetCapacity();
        T DelayValue = m_DelayLine.Read(Delay);
        m_DelayLine.Write(In + Feedback * DelayValue);
        return DelayValue;
    }

private:
    const T m_SamplingFrequency;
    CDelayLine2<T> m_DelayLine;
};
