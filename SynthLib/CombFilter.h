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

template<class T>
class CExtendedCombFilter
{
public:
    CExtendedCombFilter(int Capacity)
     : m_Capacity(Capacity)
     , m_InDelayLine(Capacity, 0)
     , m_OutDelayLine(Capacity, 0)
    {}

    // https://ccrma.stanford.edu/~jos/pasp/Allpass_Two_Combs.html (direct form I)
    // allpass filter : Bm = 1, Am = B0
    // feedback comb filter: B0 = 1, Bm=0, Am = -feedback
    // ...
    T operator()(T In, T B0, T Bm, T Am, int Delay)
    {
        Delay = Delay<m_Capacity ? Delay : m_Capacity;

        T Out = B0*In + Bm*m_InDelayLine.Read(Delay) - Am*m_OutDelayLine.Read(Delay);
        m_InDelayLine.Write(In);
        m_OutDelayLine.Write(Out);

        return Out;
    }

private:
    const int m_Capacity;
    CDelayLine2<T> m_InDelayLine;
    CDelayLine2<T> m_OutDelayLine;
};
