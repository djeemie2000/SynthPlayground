#ifndef OSCILLATORSTAGE_H
#define OSCILLATORSTAGE_H


#include <array>
#include "PhaseStep.h"
#include "PhaseGenerator.h"
#include "SelectableOperator.h"
#include "SelectableCombinor.h"
#include "Conversions.h"

template<class T>
class CCombinedOperatorStage
{
public:
    static constexpr int NumOsc = 2;

    CCombinedOperatorStage(int SamplingFrequency, const CSelectableOperator<T>& Oscillator, const CSelectableCombinor<T>& Combinor)
     : m_Frequency(440)
     , m_Dephase(0)
     , m_Oscillator()
     , m_Combinor(Combinor)
    {
        m_Oscillator.fill({1/static_cast<T>(NumOsc), 0, 1, CPhaseStep<T>(SamplingFrequency), CPhaseGenerator<T>(), Oscillator});
        SetFrequency(m_Frequency);
    }

    T operator()()
    {
        return m_Combinor(m_Oscillator[0](), m_Oscillator[1]());
    }

    void Sync()
    {
        for(auto& Osc : m_Oscillator)
        {
            Osc.s_PhaseGenerator.Sync(Osc.s_PhaseShift);
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

    void SelectCombinor(int Selected)
    {
        m_Combinor.Select(Selected);
    }

    void Select(int Oscillator, int Selected)
    {
        m_Oscillator[Oscillator].s_Oscillator.Select(Selected);
    }

    void SetAmplitude(int Oscillator, const T& Amplitude)
    {
        m_Oscillator[Oscillator].s_Amplitude = Amplitude;
    }

    void SetPhaseShift(int Oscillator, const T& PhaseShift)
    {
        m_Oscillator[Oscillator].s_PhaseShift = PhaseShift;
        Sync();
        // or:
        // m_Oscillator[Oscillator].s_PhaseGenerator.SetPhase(m_Oscillator[Oscillator].s_PhaseShift);
    }

    void SetFrequencyMultiplier(int Oscillator, const T& FrequencyMultiplier)
    {
        m_Oscillator[Oscillator].s_FrequencyMultiplier = FrequencyMultiplier;
        m_Oscillator[Oscillator].s_PhaseStep.SetFrequency(FrequencyMultiplier*m_Frequency);
    }

private:
    struct SOsc
    {
        T s_Amplitude;
        T s_PhaseShift;
        T s_FrequencyMultiplier;
        CPhaseStep<T> s_PhaseStep;
        CPhaseGenerator<T> s_PhaseGenerator;
        CSelectableOperator<T> s_Oscillator;

        T operator()()
        {
            return s_Amplitude*s_Oscillator(s_PhaseGenerator(s_PhaseStep()));
        }
    };

    T m_Frequency;
    T m_Dephase;
    std::array<SOsc, NumOsc> m_Oscillator;
    CSelectableCombinor<T> m_Combinor;
};

#endif // OSCILLATORSTAGE_H
