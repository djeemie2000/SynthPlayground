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
     , m_Depth(N)
     , m_Dephase(0)
     , m_Oscillator()
    {
        m_Oscillator.fill({1/static_cast<T>(N), 0, 1, CPhaseStep<T>(SamplingFrequency), CPhaseAccumulator<T>(), Oscillator});
        SetFrequency(m_Frequency);
        Select(0);// necessary?
        DePhase(m_Dephase);
    }

    T operator()()
    {
        T Out = 0;
        for(auto& Osc : m_Oscillator)
        {
            Out += Osc();
        }
        return Out;
    }

    void Sync()
    {
        for(auto& Osc : m_Oscillator)
        {
            Osc.s_PhaseGenerator.Set(Osc.s_PhaseShift);
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
        T Mult = 1;
        for(auto& Osc : m_Oscillator)
        {
            Osc.s_FrequencyMultiplier = Mult;
            Mult *= Detune;
        }

        SetFrequency(m_Frequency);
    }

    void DePhase(const T& Dephase)
    {
        m_Dephase = Dephase;

        T PhaseShift = 0;
        T PhaseShiftIncrease = Dephase/static_cast<T>(m_Depth);
        for(auto& Osc : m_Oscillator)
        {
            Osc.s_PhaseShift = PhaseShift;
            PhaseShift += PhaseShiftIncrease;
        }

        Sync();//?
    }

    void SetDepth(int Depth)
    {
        m_Depth = Depth;

        T Amplitude = 1/static_cast<T>(Depth);
        int idx = 0;
        for(auto& Osc : m_Oscillator)
        {
            Osc.s_Amplitude = idx<Depth ? Amplitude : 0;
            ++idx;
        }

        // need to re-calculate the dephase depending on the new depth
        DePhase(m_Dephase);
    }

private:
    struct SOsc
    {
        T s_Amplitude;
        T s_PhaseShift;
        T s_FrequencyMultiplier;
        CPhaseStep<T> s_PhaseStep;
        CPhaseAccumulator<T> s_PhaseGenerator;
        CSelectableOperator<T> s_Oscillator;

        T operator()()
        {
            return s_Amplitude*s_Oscillator(s_PhaseGenerator(s_PhaseStep()));
        }
    };

    T m_Frequency;
    int m_Depth;
    T m_Dephase;
    std::array<SOsc, N> m_Oscillator;
};

#endif // DETUNEDSELECTABLEOSCILLATOR_H
