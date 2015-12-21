#pragma once

#include <vector>
#include <string>
#include "IntConversions.h"
#include "IntOperators.h"
#include "IntPhaseGenerator.h"
#include "IntCombinors.h"
#include "IntCombinorFactory.h"
#include "IntUtilities.h"
#include "IntModulatedCombinors.h"

namespace isl
{

template<int OperatorScale, int FrequencyScale, int StrengthScale>
class CIntCombinedOperatorV2
{
public:
    CIntCombinedOperatorV2()
        : m_SamplingFrequencyHz(10000)
        , m_PhaseGenA()
        , m_PhaseGenB()
        , m_OperatorA(0)
        , m_OperatorB(0)
        , m_Combinor1(0)
        , m_FrequencyMilliHz(110*1000)
        , m_FrequencyMultiplierValueA(1<<FrequencyScale)
        , m_FrequencyMultiplierValueB(1<<FrequencyScale)
        , m_Combinor1Strength(0)
    {
        UpdateFrequency();
        SelectCombinor1(0);
        SelectOperatorA(0);
        SelectOperatorB(0);
    }

    void Sync()
    {
        m_PhaseGenA.Sync();
        m_PhaseGenB.Sync();
    }

    void SetFrequency(uint64_t FrequencyMilliHz)
    {
        m_FrequencyMilliHz = FrequencyMilliHz;

        UpdateFrequency();
    }

    void SetSamplingFrequency(uint64_t SamplingFrequency)
    {
        m_SamplingFrequencyHz = SamplingFrequency;

        UpdateFrequency();
    }

    void SetFrequencyMultiplierA(int Multiplier)
    {
        m_FrequencyMultiplierValueA = Multiplier;

        m_PhaseGenA.SetFrequency(m_SamplingFrequencyHz,
                                 m_FrequencyMilliHz*m_FrequencyMultiplierValueA >> FrequencyScale);
    }

    void SetFrequencyMultiplierB(int Multiplier)
    {
        m_FrequencyMultiplierValueB = Multiplier;

        m_PhaseGenB.SetFrequency(m_SamplingFrequencyHz,
                                 m_FrequencyMilliHz*m_FrequencyMultiplierValueB >> FrequencyScale);
    }

    void SelectOperatorA(int Idx)
    {
        m_OperatorA = GetOperator(Idx);
    }

    void SelectOperatorB(int Idx)
    {
        m_OperatorB = GetOperator(Idx);
    }

    void SelectCombinor1(int Idx)
    {
        if(Idx==0)
        {
            m_Combinor1 = IntModulatedAdd<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==1)
        {
            m_Combinor1 = IntModulatedHardLimitAdd<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==2)
        {
            m_Combinor1 = IntModulatedMult<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==3)
        {
            m_Combinor1 = IntModulatedHardLimitDiff<int, OperatorScale, StrengthScale>;
        }
    }

    void SetCombinor1Strength(int Strength)
    {
        m_Combinor1Strength = Strength;
    }

    int operator()()
    {
        int Carrier = m_OperatorA(m_PhaseGenA());
        int Modulator = m_OperatorB(m_PhaseGenB());
        return m_Combinor1(Carrier, Modulator, m_Combinor1Strength);
    }

    static std::vector<std::string> GetOperatorNames()
    {
        return { "Triangle", "Sin", "Sinh", "Saw+", "Saw-", "Pulse+", "Pulse-", "Quadratic" };
    }

    static std::vector<std::string> GetCombinorNames()
    {
        return CCombinorFactory<OperatorScale>::AvailableOperatorNames();
    }

private:
    static IntOperator GetOperator(int Idx)
    {
        if(Idx == 0)
        {
            return IntTriangle<OperatorScale>;
        }
        else if(Idx == 1)
        {
            return IntFullPseudoSin<OperatorScale>;
        }
        else if(Idx == 2)
        {
            return IntSemiPseudoSin<OperatorScale>;
        }
        else if(Idx == 3)
        {
            return IntSawUp<OperatorScale>;
        }
        else if(Idx == 4)
        {
            return IntSawDown<OperatorScale>;
        }
        else if(Idx == 5)
        {
            return IntPulsePos<OperatorScale>;
        }
        else if(Idx == 6)
        {
            return IntPulseNeg<OperatorScale>;
        }
        else if(Idx == 7)
        {
            return IntQuadratic<OperatorScale>;
        }
        return IntNoOp<OperatorScale>;
    }

    void UpdateFrequency()
    {
        m_PhaseGenA.SetFrequency(m_SamplingFrequencyHz, m_FrequencyMilliHz*m_FrequencyMultiplierValueA >> FrequencyScale);
        m_PhaseGenB.SetFrequency(m_SamplingFrequencyHz, m_FrequencyMilliHz*m_FrequencyMultiplierValueB >> FrequencyScale);
    }

    uint64_t m_SamplingFrequencyHz;

    CIntegerPhaseGenerator<int, OperatorScale> m_PhaseGenA;
    CIntegerPhaseGenerator<int, OperatorScale> m_PhaseGenB;
    IntOperator m_OperatorA;
    IntOperator m_OperatorB;
    IntModulatedCombinor m_Combinor1;

    uint64_t m_FrequencyMilliHz;
    int m_FrequencyMultiplierValueA;
    int m_FrequencyMultiplierValueB;
    int m_Combinor1Strength;
};

}//namespace isl
