#ifndef LFO_H
#define LFO_H

#include "PhaseStep.h"
#include "PhaseGenerator.h"
#include "SelectableOperator.h"

template<class T>
class CLFO
{
public:
    CLFO(const T& SamplingFrequency, const CSelectableOperator<T>& Op)
        : m_PhaseStep(SamplingFrequency)
        , m_PhaseGen()
        , m_Op(Op)
    {
        SetFrequency(1);
        SelectWaveform(0);
    }

    void SetFrequency(T Frequency)
    {
        m_PhaseStep.SetFrequency(Frequency);
    }

    void SelectWaveform(int Selected)
    {
        m_Op.Select(Selected);
    }

    T operator()()
    {
        return m_Op(m_PhaseGen(m_PhaseStep()));
    }

private:
    CPhaseStep<T> m_PhaseStep;
    CPhaseGenerator<T> m_PhaseGen;
    CSelectableOperator<T> m_Op;
};

#endif // LFO_H
