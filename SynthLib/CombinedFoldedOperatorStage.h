#ifndef OSCILLATORSTAGE_H
#define OSCILLATORSTAGE_H


#include <array>
#include "PhaseStep.h"
#include "PhaseGenerator.h"
#include "SelectableOperator.h"
#include "SelectableCombinor.h"
#include "Conversions.h"
#include "SymmetricalOperator.h"
#include "WaveFolder.h"

template<class T>
class CCombinedFoldedOperatorStage
{
public:
    static constexpr int NumOsc = 2;

    CCombinedFoldedOperatorStage(int SamplingFrequency, const CSelectableOperator<T>& Oscillator, const CSelectableCombinor<T>& Combinor)
     : m_Frequency(440)
     , m_Dephase(0)
     , m_Oscillator()
     , m_Combinor(Combinor)
    {
        m_Oscillator.fill({1/static_cast<T>(NumOsc), 0, 1, 0.97, 0.0, CPhaseStep<T>(SamplingFrequency), CPhaseGenerator<T>(), Oscillator, CSymmetricalOperator<T>(), CWaveFold2<T>()});
        SetFrequency(m_Frequency);
    }

    T operator()()
    {
        return m_Combinor(m_Oscillator[0](), m_Oscillator[1]());
    }

    T operator()(T ModIn1, T ModIn2)
    {
        return m_Combinor(m_Oscillator[0](ModIn1), m_Oscillator[1](ModIn2));
    }

    void Sync()
    {
        for(auto& Osc : m_Oscillator)
        {
            Osc.s_PhaseGenerator.Set(-1+Osc.s_PhaseShift);
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

    void SetFold(int Oscillator, T Fold)
    {
        m_Oscillator[Oscillator].s_Fold = Fold;
    }

    void SetFoldModAmount(int Oscillator, T Amount)
    {
        m_Oscillator[Oscillator].s_ModAmount = Amount;
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
        T s_Fold;
        T s_ModAmount;
        CPhaseStep<T> s_PhaseStep;
        CPhaseGenerator<T> s_PhaseGenerator;
        CSelectableOperator<T> s_Oscillator;
        CSymmetricalOperator<float> s_Symm;
        CWaveFold2<T> s_Folder;

        T operator()()
        {
            return s_Amplitude*s_Symm(s_Oscillator(s_PhaseGenerator(s_PhaseStep())), s_Folder, s_Fold);
        }
        T operator()(T ModIn)
        {
            return s_Amplitude*s_Symm(s_Oscillator(s_PhaseGenerator(s_PhaseStep())), s_Folder, s_Fold+s_ModAmount*ModIn);
        }
    };

    T m_Frequency;
    T m_Dephase;
    std::array<SOsc, NumOsc> m_Oscillator;
    CSelectableCombinor<T> m_Combinor;
};

#endif // OSCILLATORSTAGE_H
