#ifndef KARPLUSSTRONG
#define KARPLUSSTRONG

#include "Noise.h"
#include "DelayLine2.h"
#include "Trigger.h"
#include "OnePoleFilter.h"

template<class T>
class CKarplusStrong
{
public:
    CKarplusStrong(int SamplingFrequency, T MinFrequency)
        : m_SamplingFrequency(SamplingFrequency)
        , m_Period(m_SamplingFrequency/MinFrequency)
        , m_Cntr(0)// not excited
        , m_Noise()
        , m_DelayLine(m_Period, 0)//capacity of delayline determined by lowest frequency
        , m_Trigger()
    {}

    T operator()(T Trigger, T Frequency, T Cutoff)
    {
        if(m_Trigger.IsTriggerOn(Trigger))
        {
            Excite(Frequency);
        }

        T Noise = m_Noise();
        T WriteValue = 0<m_Cntr ? Noise : m_LPF(m_DelayLine.Read(m_Period), Cutoff);
        m_DelayLine.Write(WriteValue);
        if(m_Cntr)
        {
            --m_Cntr;
        }

        return WriteValue;//???m_DelayLine.Read(m_Period);
    }

private:
    void Excite(T Frequency)
    {
        m_Period = m_SamplingFrequency/Frequency;
        m_Cntr = m_Period;
    }

    int m_SamplingFrequency;
    int m_Period;
    int m_Cntr;
    CNoise<T> m_Noise;
    CDelayLine2<T> m_DelayLine;//used as circular buffer
    CTriggerIn<T> m_Trigger;
    COnePoleLowPassFilter<T> m_LPF;
};

#endif // KARPLUSSTRONG

