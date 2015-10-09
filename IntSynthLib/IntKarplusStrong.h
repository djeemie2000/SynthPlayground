#pragma once

#include "IntNoise.h"
#include "IntDelayLine.h"
#include "IntOnePoleFilter.h"

namespace isl
{

//TODO
//capacity of delayline determined by lowest frequency
// ...

template<class T, int Scale, int Capacity, int NumOperators>
class CKarplusStrong
{
public:
    static const int LPFScale = 12;//???

    CKarplusStrong()
        //: m_MinFrequency(MinFrequency)
        : m_SamplingFrequencyHz(40000)
        , m_ExciterNoise()
        , m_ExciterLPF()
        , m_Operator()
        , m_CurrentOperator(0)
        , m_NumOperators(NumOperators)
    {
    }

    void SetSamplingFrequency(std::uint64_t SamplingFrequencyHz)
    {
        m_SamplingFrequencyHz = SamplingFrequencyHz;
    }

    void SetNumOperators(int Num)
    {
        if(0<Num && Num<=NumOperators)
        {
            m_NumOperators = Num;
        }
    }

    void Excite(T Excitation, T FrequencyMilliHz, T Damp)
    {
        m_ExciterLPF.SetParameter(Excitation);
        //TODO ?

        m_Operator[m_CurrentOperator].m_DampLPF.SetParameter(Damp);
        m_Operator[m_CurrentOperator].m_Period = m_SamplingFrequencyHz*1000/FrequencyMilliHz;
        m_Operator[m_CurrentOperator].m_Cntr = m_Operator[m_CurrentOperator].m_Period;

        m_CurrentOperator = (m_CurrentOperator+1)%m_NumOperators;
    }

    T operator()()
    {
        T Excite = m_ExciterLPF(m_ExciterLPF(m_ExciterNoise()));

        T Out = 0;
        for(int idx = 0; idx<NumOperators; ++idx)
        {
            Out += m_Operator[idx](Excite);
        }
        return 2*Out/NumOperators;//??? what is a good normalisation???
    }


private:
    struct SOperator
    {
        SOperator()
            : m_Period(1)
            , m_Cntr(0)// not excited
            , m_DelayLine()
            , m_DampLPF()
        {}

        T operator()(T Excite)
        {
            T WriteValue = 0<m_Cntr ? Excite : m_DampLPF(m_DampLPF(m_DelayLine.Read(m_Period)));
            m_DelayLine.Write(WriteValue);
            if(m_Cntr)
            {
                --m_Cntr;
            }

            return WriteValue;
        }

        int m_Period;
        int m_Cntr;
        CDelayLine<T, Capacity> m_DelayLine;//used as circular buffer
        CIntegerOnePoleLowPassFilter<T, LPFScale> m_DampLPF;
    };

    //const T m_MinFrequency;
    std::uint64_t m_SamplingFrequencyHz;

    CIntegerNoise<Scale> m_ExciterNoise;
    CIntegerOnePoleLowPassFilter<T, LPFScale> m_ExciterLPF;

    SOperator m_Operator[NumOperators];
    int m_CurrentOperator;
    int m_NumOperators;
};

}
