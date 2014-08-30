#ifndef SIMPLEOSCILLATOR_H
#define SIMPLEOSCILLATOR_H

#include "PhaseStep.h"
#include "PhaseGenerator.h"
#include "SelectableOperator.h"
#include "SelectableOperatorFactory.h"

template<class T>
class CSimpleOscillator
{
public:
    CSimpleOscillator(T SamplingFrequency)
     : m_PhaseStep(SamplingFrequency)
     , m_PhaseGen()
     , m_Operator(CSelectableOperatorFactory::Create())
    {}

    void Sync()
    {
        m_PhaseGen.Sync();
    }

    void SelectWaveform(int Selection)
    {
        m_Operator.Select(Selection);
    }

    T operator()(T Frequency)
    {
        return m_Operator(m_PhaseGen(m_PhaseStep(Frequency)));
    }

private:
    CPhaseStep<T> m_PhaseStep;
    CPhaseGenerator<T> m_PhaseGen;
    CSelectableOperator<T> m_Operator;
};

#endif // SIMPLEOSCILLATOR_H
