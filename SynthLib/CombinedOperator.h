#pragma once

#include <vector>
#include <functional>
#include "Combinor.h"
#include "PhaseShifter.h"
#include "PhaseStep.h"
#include "PhaseAccumulator.h"
#include "SelectableCombinor.h"
#include "SelectableOperator.h"
#include "Triangle.h"
#include "FullPseudoSin.h"
#include "PseudoSin.h"
#include "RampUp.h"
#include "RampDown.h"
#include "Pulse.h"
#include "NoOp.h"

template<class T>
class CCombinedOperator
{
public:
    CCombinedOperator(T SamplingFrequency)
        : m_PhaseStepA(SamplingFrequency)
        , m_PhaseAccumulatorA()
        , m_PhaseShifterA()
        , m_OperatorA()
        , m_PhaseStepB(SamplingFrequency)
        , m_PhaseAccumulatorB()
        , m_PhaseShifterB()
        , m_OperatorB()
        , m_Combinor()
    {
        // factory for operators and combinor: add and select default
        m_Combinor.Add(CAdd<T>());// +
        m_Combinor.Add(CHardLimitAdd<T>());// +L

        m_Combinor.Add(CMultFirst<T>());//*A
        m_Combinor.Add(CMultSecond<T>());//*B
        m_Combinor.Add(CMult<T>());//*

        m_Combinor.Add(CHardLimitDiff<float>());//-L
        m_Combinor.Add(CDiffAbs<float>());//-||

        m_Combinor.Add(CMaxAbs<float>());//M||
        m_Combinor.Add(CMinAbs<float>());//m||
        m_Combinor.Add(CMax<float>());//M
        m_Combinor.Add(CMin<float>());//m

        m_Combinor.Add(CPosNegAdd<float>());//P+N
        m_Combinor.Add(CNegPosAdd<float>());//N+P

        m_Combinor.Add(CRingModFirst<float>());//RA
        m_Combinor.Add(CRingModSecond<float>());//RB

        m_Combinor.Add(CMultMod1<float>());//A*(1+B)
        m_Combinor.Add(CMultMod2<float>());//B*(1+A)

        m_Combinor.Add(CMultUnipolar<float>());//*U

        m_Combinor.Select(0);//default


        //
        m_OperatorA.Add(CTriangle<float>());
        m_OperatorA.Add(CFullPseudoSin<float>());
        m_OperatorA.Add(CPseudoSin<float>());
        m_OperatorA.Add(CRampUp<float>());
        m_OperatorA.Add(CRampDown<float>());
        m_OperatorA.Add(CPulsePos<float>());
        m_OperatorA.Add(CPulseNeg<float>());
        m_OperatorA.Add(CNoOp<float>());

        m_OperatorA.Select(0);//default

        m_OperatorB.Add(CTriangle<float>());
        m_OperatorB.Add(CFullPseudoSin<float>());
        m_OperatorB.Add(CPseudoSin<float>());
        m_OperatorB.Add(CRampUp<float>());
        m_OperatorB.Add(CRampDown<float>());
        m_OperatorB.Add(CPulsePos<float>());
        m_OperatorB.Add(CPulseNeg<float>());
        m_OperatorB.Add(CNoOp<float>());

        m_OperatorB.Select(0);//default

    }

    // names for combinors
    static std::vector<std::string> GetCombinorNames()
    {
        return { "+", "+L", "*A", "*B", "*", "-L", "-||", "M||", "m||", "M", "m", "P+N", "N+P", "RA", "RB", "A*(1+B)", "B*(1+A)", "*U" };
    }
    // names for operators
    static std::vector<std::string> GetOperatorNames()
    {
        return { "Triangle", "Sin", "Sinh", "SawUp", "SawDown", "Pulse+", "Pulse-", "NoOp" };
    }

    void SelectOperatorA(int Selected)
    {
        m_OperatorA.Select(Selected);
    }

    void SelectOperatorB(int Selected)
    {
        m_OperatorB.Select(Selected);
    }

    void SelectCombinor(int Selected)
    {
        m_Combinor.Select(Selected);
    }

    float operator()(T Frequency, T FrequencyMultiplierA, T PhaseShiftA, T FrequencyMultiplierB, T PhaseShiftB)
    {
        return m_Combinor( m_OperatorA(m_PhaseShifterA(m_PhaseAccumulatorA(m_PhaseStepA(Frequency*FrequencyMultiplierA)), PhaseShiftA)),
                           m_OperatorB(m_PhaseShifterB(m_PhaseAccumulatorB(m_PhaseStepB(Frequency*FrequencyMultiplierB)), PhaseShiftB)) );
    }

private:
    CPhaseStep<T> m_PhaseStepA;
    CPhaseAccumulator<T> m_PhaseAccumulatorA;
    CPhaseShifter<T> m_PhaseShifterA;
    CSelectableOperator<T> m_OperatorA;

    CPhaseStep<T> m_PhaseStepB;
    CPhaseAccumulator<T> m_PhaseAccumulatorB;
    CPhaseShifter<T> m_PhaseShifterB;
    CSelectableOperator<T> m_OperatorB;

    CSelectableCombinor<T> m_Combinor;
};
