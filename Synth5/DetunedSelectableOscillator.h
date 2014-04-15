#ifndef DETUNEDSELECTABLEOSCILLATOR_H
#define DETUNEDSELECTABLEOSCILLATOR_H

#include <array>
#include "PhaseStep.h"
#include "PhaseGenerator.h"
#include "SelectableOperator.h"

template<class T, int N>
class CDetunedSelectableOscillator
{
public:
    CDetunedSelectableOscillator(int SamplingFrequency, const CSelectableOperator<T>& Oscillator)
     : m_Frequency(440)
     , m_Oscillator()
    {
        m_Oscillator.fill({1, CPhaseStep<T>(SamplingFrequency), CPhaseGenerator<T>(), Oscillator});
        SetFrequency(m_Frequency);
    }

    T operator()()
    {
        T Temp = 0;
        for(auto& Osc : m_Oscillator)
        {
            Temp += Osc();
        }
        return Temp/static_cast<T>(N);
        //return m_Oscillator(m_PhaseGenerator(m_PhaseStep()));
    }

    void Sync()
    {
        for(auto& Osc : m_Oscillator)
        {
            Osc.s_PhaseGenerator.Set(0);
        }
    }

    void SetFrequency(const T& Frequency)
    {
        m_Frequency = Frequency;///remember for detune
        for(auto& Osc : m_Oscillator)
        {
            Osc.s_PhaseStep.SetFrequency(Osc.s_FrequencyMultiplier*Frequency);
        }
    }

    void Select(int Selected)
    {
        for(auto& Osc : m_Oscillator)
        {
            Osc.s_Oscillator.Select(Selected);
        }
    }

    void Detune(const T& Detune)
    {
        //TODO!!!
        T Mult = -N/2;
        for(auto& Osc : m_Oscillator)
        {
            Osc.s_FrequencyMultiplier = 1+Mult*Detune;
            Mult += 1;
        }

        SetFrequency(m_Frequency);
    }

private:
    struct SOsc
    {
        T s_FrequencyMultiplier;
        CPhaseStep<T> s_PhaseStep;
        CPhaseGenerator<T> s_PhaseGenerator;
        CSelectableOperator<T> s_Oscillator;

        T operator()()
        {
            return s_Oscillator(s_PhaseGenerator(s_PhaseStep()));
        }
    };

    T m_Frequency;
    std::array<SOsc, N> m_Oscillator;
};

#endif // DETUNEDSELECTABLEOSCILLATOR_H
