#pragma once

#include "IntPhaseGenerator.h"

template<class T, int NumSaws, int Scale>
class CIntMultiSaw
{
public:
    CIntMultiSaw()
    {
        for(int idx = 0; idx<NumSaws; ++idx)
        {
            m_PhaseShift[idx] = 0;
        }
    }

    void SetFrequency(int SamplingFrequency, int FrequencyMilliHz)
    {
        m_Phase.SetFrequency(SamplingFrequency, FrequencyMilliHz);
    }

    void SetPhaseShift(T PhaseShift, int Index)
    {
        m_PhaseShift[Index] = PhaseShift;
    }

    T operator()()
    {
        m_Phase();
        T Out = 0;
        for(int idx = 0; idx<NumSaws; ++idx)
        {
            Out += m_Phase.Shifted(m_PhaseShift[idx]);
        }
        return Out/NumSaws;
    }

    T operator()(T* PhaseShift)
    {
        m_Phase();
        T Out = 0;
        for(int idx = 0; idx<NumSaws; ++idx)
        {
            Out += m_Phase.Shifted(PhaseShift[idx]);
        }
        return Out/NumSaws;
    }


private:
    CIntegerPhaseGenerator<T, Scale> m_Phase;
    T m_PhaseShift[NumSaws];
};
