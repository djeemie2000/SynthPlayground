#pragma once

#include "IntNoise.h"
#include "IntDelayLine.h"
#include "IntOnePoleFilter.h"

namespace isl
{

//TODO
//capacity of delayline determined by lowest frequency
// ...

template<class T, int Scale, int Capacity>
class CKarplusStrong
{
public:
    static const int LPFScale = 12;//???

    CKarplusStrong()
        //: m_MinFrequency(MinFrequency)
        : m_SamplingFrequencyHz(40000)
        , m_Period(m_SamplingFrequencyHz*1000/220)
        , m_Cntr(0)// not excited
        , m_ExciterNoise()
        , m_ExciterLPF()
        , m_DelayLine()
    {
    }

    void SetSamplingFrequency(std::uint64_t SamplingFrequencyHz)
    {
        m_SamplingFrequencyHz = SamplingFrequencyHz;
    }

    void Excite(T Excitation, T FrequencyMilliHz, T Damp)
    {
        m_ExciterLPF.SetParameter(Excitation);
        //TODO ?
        m_DampLPF.SetParameter(Damp);

        m_Period = m_SamplingFrequencyHz*1000/FrequencyMilliHz;
        m_Cntr = m_Period;
    }

    T operator()()
    {
        T Excite = m_ExciterLPF(m_ExciterNoise());

        T WriteValue = 0<m_Cntr ? Excite : m_DampLPF(m_DelayLine.Read(m_Period));
        m_DelayLine.Write(WriteValue);
        if(m_Cntr)
        {
            --m_Cntr;
        }

        return WriteValue;
    }


private:
//    void Excite(T Frequency)
//    {
//        m_Period = m_SamplingFrequency/Frequency;
//        m_Cntr = m_Period;
//    }

    //const T m_MinFrequency;
    std::uint64_t m_SamplingFrequencyHz;
    int m_Period;
    int m_Cntr;
    CIntegerNoise<Scale> m_ExciterNoise;
    CIntegerOnePoleLowPassFilter<T, LPFScale> m_ExciterLPF;
    CDelayLine<T, Capacity> m_DelayLine;//used as circular buffer
    CIntegerOnePoleLowPassFilter<T, LPFScale> m_DampLPF;
};

}
