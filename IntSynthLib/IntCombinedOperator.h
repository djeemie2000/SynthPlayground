#pragma once

#include "IntConversions.h"
#include "IntOperators.h"
#include "IntPhaseGenerator.h"
#include "IntCombinors.h"

namespace isl
{

template<int Scale>
class CIntCombinedOperator
{
public:
    CIntCombinedOperator(uint64_t SamplingFrequency)
        : m_SamplingFrequencyHz(SamplingFrequency)
        , m_PhaseGenA()
        , m_PhaseGenB()
        , m_PhaseGenC()
        , m_OperatorA( IntTriangle<Scale> )
        , m_OperatorB( IntTriangle<Scale> )
        , m_OperatorC( IntTriangle<Scale> )
        , m_Combinor1( IntAdd<int, Scale> )
        , m_Combinor2( IntAdd<int, Scale> )
        , m_FrequencyMilliHz(110*1000)
        , m_FrequencyMultiplierValueA(1<<8)
        , m_FrequencyMultiplierScaleA(8)
        , m_FrequencyMultiplierValueB(1<<8)
        , m_FrequencyMultiplierScaleB(8)
        , m_FrequencyMultiplierValueC(1<<8)
        , m_FrequencyMultiplierScaleC(8)
    {
        UpdateFrequency();
        SelectCombinor1(0);
        SelectCombinor2(0);
        SelectOperatorA(0);
        SelectOperatorB(0);
        SelectOperatorC(0);
    }

    void Sync()
    {
        m_PhaseGenA.Sync();
        m_PhaseGenB.Sync();
        m_PhaseGenC.Sync();
    }

    void SetFrequency(uint64_t FrequencyMilliHz)
    {
        m_FrequencyMilliHz = FrequencyMilliHz;

        UpdateFrequency();
    }

    void SetFrequencyMultiplierA(int Multiplier, int MultiplierScale)
    {
        m_FrequencyMultiplierValueA = Multiplier;
        m_FrequencyMultiplierScaleA = MultiplierScale;

        m_PhaseGenA.SetFrequency(m_SamplingFrequencyHz,
                                 m_FrequencyMilliHz*m_FrequencyMultiplierValueA >> m_FrequencyMultiplierScaleA);
    }

    void SetFrequencyMultiplierB(int Multiplier, int MultiplierScale)
    {
        m_FrequencyMultiplierValueB = Multiplier;
        m_FrequencyMultiplierScaleB = MultiplierScale;

        m_PhaseGenB.SetFrequency(m_SamplingFrequencyHz,
                                 m_FrequencyMilliHz*m_FrequencyMultiplierValueB >> m_FrequencyMultiplierScaleB);
    }

    void SetFrequencyMultiplierC(int Multiplier, int MultiplierScale)
    {
        m_FrequencyMultiplierValueC = Multiplier;
        m_FrequencyMultiplierScaleC = MultiplierScale;

        m_PhaseGenC.SetFrequency(m_SamplingFrequencyHz,
                                 m_FrequencyMilliHz*m_FrequencyMultiplierValueC >> m_FrequencyMultiplierScaleC);
    }

    void SelectOperatorA(int Idx)
    {
        if(Idx == 0)
        {
            m_OperatorA = IntTriangle<Scale>;
        }
        else if(Idx == 1)
        {
            m_OperatorA = IntFullPseudoSin<Scale>;
        }
        else if(Idx == 2)
        {
            m_OperatorA = IntSemiPseudoSin<Scale>;
        }
        else if(Idx == 3)
        {
            m_OperatorA = IntSawUp<Scale>;
        }
        else if(Idx == 4)
        {
            m_OperatorA = IntSawDown<Scale>;
        }
        else if(Idx == 5)
        {
            m_OperatorA = IntPulse<Scale>;
        }
        else if(Idx == 6)
        {
            m_OperatorA = IntQuadratic<Scale>;
        }
        else if(Idx == 7)
        {
            m_OperatorA = IntNoOp<Scale>;
        }
    }

    void SelectOperatorB(int Idx)
    {
        if(Idx == 0)
        {
            m_OperatorB = IntTriangle<Scale>;
        }
        else if(Idx == 1)
        {
            m_OperatorB = IntFullPseudoSin<Scale>;
        }
        else if(Idx == 2)
        {
            m_OperatorB = IntSemiPseudoSin<Scale>;
        }
        else if(Idx == 3)
        {
            m_OperatorB = IntSawUp<Scale>;
        }
        else if(Idx == 4)
        {
            m_OperatorB = IntSawDown<Scale>;
        }
        else if(Idx == 5)
        {
            m_OperatorB = IntPulse<Scale>;
        }
        else if(Idx == 6)
        {
            m_OperatorB = IntQuadratic<Scale>;
        }
        else if(Idx == 7)
        {
            m_OperatorB = IntNoOp<Scale>;
        }
    }

    void SelectOperatorC(int Idx)
    {
        if(Idx == 0)
        {
            m_OperatorC = IntTriangle<Scale>;
        }
        else if(Idx == 1)
        {
            m_OperatorC = IntFullPseudoSin<Scale>;
        }
        else if(Idx == 2)
        {
            m_OperatorC = IntSemiPseudoSin<Scale>;
        }
        else if(Idx == 3)
        {
            m_OperatorC = IntSawUp<Scale>;
        }
        else if(Idx == 4)
        {
            m_OperatorC = IntSawDown<Scale>;
        }
        else if(Idx == 5)
        {
            m_OperatorC = IntPulse<Scale>;
        }
        else if(Idx == 6)
        {
            m_OperatorC = IntQuadratic<Scale>;
        }
        else if(Idx == 7)
        {
            m_OperatorC = IntNoOp<Scale>;
        }
    }

    void SelectCombinor1(int Idx)
    {
        if(Idx == 0)
        {
            m_Combinor1  = IntAdd<int, Scale>;// +
        }
        else if(Idx == 1)
        {
            m_Combinor1 = IntHardLimitAdd<int, Scale>;// +L
        }
        else if(Idx == 2)
        {
            m_Combinor1 = IntMultFirst<int, Scale>;// *A
        }
        else if(Idx == 3)
        {
            m_Combinor1 = IntMultSecond<int, Scale>;// *B
        }
        else if(Idx == 4)
        {
            m_Combinor1 = IntMult<int, Scale>;// *
        }
        else if(Idx == 5)
        {
            m_Combinor1 = IntRingModFirst<int, Scale>;// RA
        }
        else if(Idx == 6)
        {
            m_Combinor1 = IntRingModSecond<int, Scale>;// RB
        }
        else if(Idx == 7)
        {
            m_Combinor1 = IntMultUnipolar<int, Scale>;// *U
        }
        else if(Idx == 8)
        {
            m_Combinor1 = IntHardLimitDiff<int, Scale>;// -L
        }
        else if(Idx == 9)
        {
            m_Combinor1 = IntDiffAbs<int, Scale>;// -||
        }
        else if(Idx == 10)
        {
            m_Combinor1 = IntMaxAbs<int, Scale>;// M||
        }
        else if(Idx == 11)
        {
            m_Combinor1 = IntMinAbs<int, Scale>;// m||
        }
        else if(Idx == 12)
        {
            m_Combinor1 = IntMax<int, Scale>;// M
        }
        else if(Idx == 13)
        {
            m_Combinor1 = IntMin<int, Scale>;// m
        }
        else if(Idx == 14)
        {
            m_Combinor1 = IntPosNegAdd<int, Scale>;// P + N
        }
        else if(Idx == 15)
        {
            m_Combinor1 = IntNegPosAdd<int, Scale>;// N + P
        }
        else if(Idx == 16)
        {
            m_Combinor1 = IntMultMod1<int, Scale>;// A(1+B)
        }
        else if(Idx == 17)
        {
            m_Combinor1 = IntMultMod2<int, Scale>;// B(1+A)
        }
    }

    void SelectCombinor2(int Idx)
    {
        if(Idx == 0)
        {
            m_Combinor2  = IntAdd<int, Scale>;// +
        }
        else if(Idx == 1)
        {
            m_Combinor2 = IntHardLimitAdd<int, Scale>;// +L
        }
        else if(Idx == 2)
        {
            m_Combinor2 = IntMultFirst<int, Scale>;// *A
        }
        else if(Idx == 3)
        {
            m_Combinor2 = IntMultSecond<int, Scale>;// *B
        }
        else if(Idx == 4)
        {
            m_Combinor2 = IntMult<int, Scale>;// *
        }
        else if(Idx == 5)
        {
            m_Combinor2 = IntRingModFirst<int, Scale>;// RA
        }
        else if(Idx == 6)
        {
            m_Combinor2 = IntRingModSecond<int, Scale>;// RB
        }
        else if(Idx == 7)
        {
            m_Combinor2 = IntMultUnipolar<int, Scale>;// *U
        }
        else if(Idx == 8)
        {
            m_Combinor2 = IntHardLimitDiff<int, Scale>;// -L
        }
        else if(Idx == 9)
        {
            m_Combinor2 = IntDiffAbs<int, Scale>;// -||
        }
        else if(Idx == 10)
        {
            m_Combinor2 = IntMaxAbs<int, Scale>;// M||
        }
        else if(Idx == 11)
        {
            m_Combinor2 = IntMinAbs<int, Scale>;// m||
        }
        else if(Idx == 12)
        {
            m_Combinor2 = IntMax<int, Scale>;// M
        }
        else if(Idx == 13)
        {
            m_Combinor2 = IntMin<int, Scale>;// m
        }
        else if(Idx == 14)
        {
            m_Combinor2 = IntPosNegAdd<int, Scale>;// P + N
        }
        else if(Idx == 15)
        {
            m_Combinor2 = IntNegPosAdd<int, Scale>;// N + P
        }
        else if(Idx == 16)
        {
            m_Combinor2 = IntMultMod1<int, Scale>;// A(1+B)
        }
        else if(Idx == 17)
        {
            m_Combinor2 = IntMultMod2<int, Scale>;// B(1+A)
        }
    }

    int operator()()
    {
        return m_Combinor2( m_Combinor1(m_OperatorA(m_PhaseGenA()), m_OperatorB(m_PhaseGenB())),
                            m_OperatorC(m_PhaseGenC()) );
    }

private:
    void UpdateFrequency()
    {
        m_PhaseGenA.SetFrequency(m_SamplingFrequencyHz, m_FrequencyMilliHz*m_FrequencyMultiplierValueA >> m_FrequencyMultiplierScaleA);
        m_PhaseGenB.SetFrequency(m_SamplingFrequencyHz, m_FrequencyMilliHz*m_FrequencyMultiplierValueB >> m_FrequencyMultiplierScaleB);
        m_PhaseGenC.SetFrequency(m_SamplingFrequencyHz, m_FrequencyMilliHz*m_FrequencyMultiplierValueC >> m_FrequencyMultiplierScaleC);
    }

    const uint64_t m_SamplingFrequencyHz;

    CIntegerPhaseGenerator<int, Scale> m_PhaseGenA;
    CIntegerPhaseGenerator<int, Scale> m_PhaseGenB;
    CIntegerPhaseGenerator<int, Scale> m_PhaseGenC;
    IntOperator m_OperatorA;
    IntOperator m_OperatorB;
    IntOperator m_OperatorC;
    IntCombinor m_Combinor1;
    IntCombinor m_Combinor2;

    uint64_t m_FrequencyMilliHz;
    int m_FrequencyMultiplierValueA;
    int m_FrequencyMultiplierScaleA;
    int m_FrequencyMultiplierValueB;
    int m_FrequencyMultiplierScaleB;
    int m_FrequencyMultiplierValueC;
    int m_FrequencyMultiplierScaleC;
};

}//namespace isl
