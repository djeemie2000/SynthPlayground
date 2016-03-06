#ifndef DELAYVERB_H
#define DELAYVERB_H

#include "DelayLine2.h"
#include "OnePoleFilter.h"

template<class T>
class CDelayVerb
{
public:
    CDelayVerb(int Capacity)
        : m_Capacity(Capacity)
        , m_MaxDelay(m_Capacity/19-DelayOffset)
        , m_DelayLine(Capacity, 0)
        , m_DampFilter()
    {
    }

    T operator()(T In, T Feedback, int Delay, T Damp)
    {
        // make sure delay is within range!
        if(Delay<0)
        {
            Delay = 0;
        }
        else if(m_MaxDelay<Delay)
        {
            Delay = m_MaxDelay;
        }

        // read delayed values
        T ReadValue = m_DelayLine.Read(DelayOffset+Delay*2)/4
                    + m_DelayLine.Read(DelayOffset+Delay*3)
                    + m_DelayLine.Read(DelayOffset+Delay*5)
                    + m_DelayLine.Read(DelayOffset+Delay*7)
                    + m_DelayLine.Read(DelayOffset+Delay*11)
                    + m_DelayLine.Read(DelayOffset+Delay*13)/2
                    + m_DelayLine.Read(DelayOffset+Delay*17)/2
                    + m_DelayLine.Read(DelayOffset+Delay*19)/2;
        ReadValue *= Normalize;

        T WriteValue = In + Feedback*m_DampFilter(ReadValue, Damp);
        m_DelayLine.Write(WriteValue);

        return WriteValue;
    }

private:
    static constexpr int NumDelays = 8;
//    static const int m_DelayMultiplier[NumDelays] = { 2, 3, 5, 7, 11, 13, 17, 19};
    static constexpr T Normalize = T(1)/NumDelays;
    static constexpr int DelayOffset = 100;
    const int m_Capacity;
    const int m_MaxDelay;
    CDelayLine2<T> m_DelayLine;
    COnePoleLowPassFilter<T> m_DampFilter;
    //COnePoleHighPassFilter<T> m_DampFilter;
};

#endif // DELAYVERB_H
