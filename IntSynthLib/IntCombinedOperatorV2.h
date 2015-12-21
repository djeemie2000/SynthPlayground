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
        , m_OperatorACarrier(true)
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
        m_Combinor1 = GetCombinor(Idx);
    }

    void SetCombinor1Strength(int Strength)
    {
        m_Combinor1Strength = Strength;
    }

    void SetOperatorACarrier(bool Carrier)
    {
        m_OperatorACarrier = Carrier;
    }

    void SetOperatorBCarrier(bool Carrier)
    {
        m_OperatorACarrier = !Carrier;
    }

    int operator()()
    {
        int OpA = m_OperatorA(m_PhaseGenA());
        int OpB = m_OperatorB(m_PhaseGenB());
        int Carrier = m_OperatorACarrier ? OpA : OpB;
        int Modulator = m_OperatorACarrier ? OpB : OpA;
        return m_Combinor1(Carrier, Modulator, m_Combinor1Strength);
    }

    static std::vector<std::string> GetOperatorNames()
    {
        return { "Triangle", "Sin", "Sinh+", "Sinh-", "Saw+", "Saw-", "Pulse+", "Pulse-", "Quadratic" };
    }

    static std::vector<std::string> GetCombinorNames()
    {
        return { "C+M", "LC+M", "C*M", "UC*UM",
                "|C|*|M|", "C*|M|", "C*UM", "LC-M",
                "C-|M|", "M", "M||", "m||",
                "m", "mC|M|", "MC|M|", "C(1+M)"};
    }

private:
    static IntModulatedCombinor GetCombinor(int Idx)
    {
        if(Idx==0)
        {
            return IntModulatedAdd<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==1)
        {
            return IntModulatedHardLimitAdd<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==2)
        {
            return IntModulatedMult<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==3)
        {
            return IntModulatedMultUnipolar<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==4)
        {
            return IntModulatedMultAbs<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==5)
        {
            return IntModulatedMultFirst<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==6)
        {
            return IntModulatedRingModFirst<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==7)
        {
            return IntModulatedHardLimitDiff<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==8)
        {
            return IntModulatedDiffAbs<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==9)
        {
            return IntModulatedMax<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==10)
        {
            return IntModulatedMaxAbs<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==11)
        {
            return IntModulatedMinAbs<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==12)
        {
            return IntModulatedMin<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==13)
        {
            return IntModulatedMinAbsSecond<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==14)
        {
            return IntModulatedMaxAbsSecond<int, OperatorScale, StrengthScale>;
        }
        else if(Idx==15)
        {
            return IntModulatedMultMod1<int, OperatorScale, StrengthScale>;
        }
        return IntModulatedAdd<int, OperatorScale, StrengthScale>;//default
    }

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
            return IntSemiPseudoSinNeg<OperatorScale>;
        }
        else if(Idx == 4)
        {
            return IntSawUp<OperatorScale>;
        }
        else if(Idx == 5)
        {
            return IntSawDown<OperatorScale>;
        }
        else if(Idx == 6)
        {
            return IntPulsePos<OperatorScale>;
        }
        else if(Idx == 7)
        {
            return IntPulseNeg<OperatorScale>;
        }
        else if(Idx == 8)
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
    bool m_OperatorACarrier;
};

}//namespace isl
