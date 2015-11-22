#pragma once

#include "Noise.h"
#include "DelayLine2.h"
#include "OnePoleFilter.h"
#include "DeltaSmooth.h"
#include "AREnvelope.h"
#include "ConstNumSamplesGenerator.h"

namespace synthlib
{

//TODO
//capacity of delayline determined by lowest frequency
// ...

template<class T, int Capacity, int NumOperators>
class CPolyKarplusStrong
{
public:

    CPolyKarplusStrong()
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

    void Excite(T Excitation, T Frequency, T Damp, T AttackMilliSeconds)
    {
        m_ExciterLPF.SetParameter(Excitation);
        T Period = m_SamplingFrequencyHz/Frequency;
        if(Period<Capacity)
        {
            T AttackSamples = CConstNumSamplesGenerator<float>(m_SamplingFrequencyHz).SetMilliSeconds(AttackMilliSeconds);

            m_Operator[m_CurrentOperator].ExciteOperator(Damp, Period, AttackSamples);

            m_CurrentOperator = (m_CurrentOperator+1)%m_NumOperators;
        }
    }

    T operator()()
    {
        T Excite = m_ExciterLPF(m_ExciterLPF(m_ExciterLPF(m_ExciterLPF(m_ExciterNoise()))));

        T Out = 0;
        for(int idx = 0; idx<NumOperators; ++idx)
        {
            Out += m_Operator[idx](Excite);
        }

        return Out;//no normalisation
    }


private:
    struct SOperator
    {
        SOperator()
            : m_Period(1)
            , m_Cntr(0)// not excited
            , m_DelayLine(Capacity, 0)
            , m_DampLPF()
            , m_DCOffset(0, T(1)/2048)
            , m_Envelope()
        {}

        void ExciteOperator(T Damp, int Period, T AttackSamples)
        {
            m_DampLPF.SetParameter(Damp);
            m_DCOffset.Reset(0);
            m_Envelope.NoteOn();
            m_Envelope.SetAttackSamples(AttackSamples);
            m_Period = Period;
            m_Cntr = m_Period;
        }

        T operator()(T Excite)
        {
            T WriteValue = 0<m_Cntr ? Excite : m_DampLPF(m_DampLPF(m_DampLPF(m_DampLPF(m_DelayLine.Read(m_Period)))));
            m_DelayLine.Write(WriteValue);
            if(m_Cntr)
            {
                --m_Cntr;
            }

            return m_Envelope()*(WriteValue-m_DCOffset(WriteValue));//m_Envelope(WriteValue-m_DCOffset(WriteValue));//
        }

        int m_Period;
        int m_Cntr;
        CDelayLine2<T> m_DelayLine;//used as circular buffer
        COnePoleLowPassFilter<T> m_DampLPF;
        synthlib::CDeltaSmooth<T> m_DCOffset;
        CAREnvelope<T> m_Envelope;
    };

    //const T m_MinFrequency;
    std::uint64_t m_SamplingFrequencyHz;

    CNoise<T> m_ExciterNoise;
    COnePoleLowPassFilter<T> m_ExciterLPF;

    SOperator m_Operator[NumOperators];
    int m_CurrentOperator;
    int m_NumOperators;    
};

}
