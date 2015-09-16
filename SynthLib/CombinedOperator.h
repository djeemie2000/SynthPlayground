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
        , m_PhaseStepC(SamplingFrequency)
        , m_PhaseAccumulatorC()
        , m_PhaseShifterC()
        , m_OperatorC()
        , m_Combinor2()
    {
        CreateCombinor(m_Combinor);
        CreateCombinor(m_Combinor2);

        CreateOperator(m_OperatorA);
        CreateOperator(m_OperatorB);
        CreateOperator(m_OperatorC);
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

    void SelectOperatorC(int Selected)
    {
        m_OperatorC.Select(Selected);
    }

    void SelectCombinor(int Selected)
    {
        m_Combinor.Select(Selected);
    }

    void SelectCombinor2(int Selected)
    {
        m_Combinor2.Select(Selected);
    }

    float operator()(T Frequency,
                     T FrequencyMultiplierA, T PhaseShiftA,
                     T FrequencyMultiplierB, T PhaseShiftB)
    {
        return m_Combinor( m_OperatorA(m_PhaseShifterA(m_PhaseAccumulatorA(m_PhaseStepA(Frequency*FrequencyMultiplierA)), PhaseShiftA)),
                           m_OperatorB(m_PhaseShifterB(m_PhaseAccumulatorB(m_PhaseStepB(Frequency*FrequencyMultiplierB)), PhaseShiftB)) );
    }

    float operator()(T Frequency,
                     T FrequencyMultiplierA, T PhaseShiftA,
                     T FrequencyMultiplierB, T PhaseShiftB,
                     T FrequencyMultiplierC, T PhaseShiftC)
    {
        return m_Combinor2(m_Combinor( m_OperatorA(m_PhaseShifterA(m_PhaseAccumulatorA(m_PhaseStepA(Frequency*FrequencyMultiplierA)), PhaseShiftA)),
                                       m_OperatorB(m_PhaseShifterB(m_PhaseAccumulatorB(m_PhaseStepB(Frequency*FrequencyMultiplierB)), PhaseShiftB)) ),
                           m_OperatorC(m_PhaseShifterC(m_PhaseAccumulatorC(m_PhaseStepC(Frequency*FrequencyMultiplierC)), PhaseShiftC)) );
    }

private:
    void CreateCombinor(CSelectableCombinor<T>& Combinor)
    {
        // factory for operators and combinor: add and select default
        Combinor.Add(CAdd<T>());// +
        Combinor.Add(CHardLimitAdd<T>());// +L

        Combinor.Add(CMultFirst<T>());//*A
        Combinor.Add(CMultSecond<T>());//*B
        Combinor.Add(CMult<T>());//*

        Combinor.Add(CHardLimitDiff<float>());//-L
        Combinor.Add(CDiffAbs<float>());//-||

        Combinor.Add(CMaxAbs<float>());//M||
        Combinor.Add(CMinAbs<float>());//m||
        Combinor.Add(CMax<float>());//M
        Combinor.Add(CMin<float>());//m

        Combinor.Add(CPosNegAdd<float>());//P+N
        Combinor.Add(CNegPosAdd<float>());//N+P

        Combinor.Add(CRingModFirst<float>());//RA
        Combinor.Add(CRingModSecond<float>());//RB

        Combinor.Add(CMultMod1<float>());//A*(1+B)
        Combinor.Add(CMultMod2<float>());//B*(1+A)

        Combinor.Add(CMultUnipolar<float>());//*U

        Combinor.Select(0);//default
    }

    void CreateOperator(CSelectableOperator<T>& Operator)
    {
        Operator.Add(CTriangle<float>());
        Operator.Add(CFullPseudoSin<float>());
        Operator.Add(CPseudoSin<float>());
        Operator.Add(CRampUp<float>());
        Operator.Add(CRampDown<float>());
        Operator.Add(CPulsePos<float>());
        Operator.Add(CPulseNeg<float>());
        Operator.Add(CNoOp<float>());

        Operator.Select(0);//default
    }

    CPhaseStep<T> m_PhaseStepA;
    CPhaseAccumulator<T> m_PhaseAccumulatorA;
    CPhaseShifter<T> m_PhaseShifterA;
    CSelectableOperator<T> m_OperatorA;

    CPhaseStep<T> m_PhaseStepB;
    CPhaseAccumulator<T> m_PhaseAccumulatorB;
    CPhaseShifter<T> m_PhaseShifterB;
    CSelectableOperator<T> m_OperatorB;

    CSelectableCombinor<T> m_Combinor;

    CPhaseStep<T> m_PhaseStepC;
    CPhaseAccumulator<T> m_PhaseAccumulatorC;
    CPhaseShifter<T> m_PhaseShifterC;
    CSelectableOperator<T> m_OperatorC;

    CSelectableCombinor<T> m_Combinor2;
};
