#ifndef SKEWEDINTERPOLATINGOPERATOR_H
#define SKEWEDINTERPOLATINGOPERATOR_H

#include "PhaseStep.h"
#include "PhaseGenerator.h"
#include "SelectableOperator.h"
#include "ConstGenerator.h"
#include "CrossFader.h"
#include "Modulator.h"
#include "PhaseSkewer.h"

template<class T>
class CSkewedInterpolatingOperator
{
public:
    CSkewedInterpolatingOperator(int SamplingFrequency, const CSelectableOperator<T>& Operator)
     : m_PhaseStep(SamplingFrequency)
     , m_PhaseGenerator()
     , m_Skew()
     , m_SkewModulator()
     , m_Skewer()
     , m_Operator1(Operator)
     , m_Operator2(Operator)
     , m_Mix()
     , m_MixModulator()
     , m_CrossFader()
    {
        m_Mix.Set(0);
        m_Skew.Set(0);
        m_Operator1.Select(0);
        m_Operator2.Select(0);
    }

    void SetFrequency(T Frequency)
    {
        m_PhaseStep.SetFrequency(Frequency);
    }

    void SelectOperator1(int Selected)
    {
        m_Operator1.Select(Selected);
    }

    void SelectOperator2(int Selected)
    {
        m_Operator2.Select(Selected);
    }

    void SetMix(T Mix)
    {
        m_Mix.Set(Mix);
    }

    void SetMixModAmt(T ModAmt)
    {
        m_MixModulator.SetModAmount(ModAmt);
    }

    void SetSkew(T Skew)
    {
        m_Skew.Set(Skew);
    }

    void SetSkewModAmt(T ModAmt)
    {
        m_SkewModulator.SetModAmount(ModAmt);
    }

    T operator()()
    {
        return m_CrossFader(m_Operator1, m_Operator2, m_Skewer(m_PhaseGenerator(m_PhaseStep()), m_Skew()), m_Mix());
    }

    T operator()(T MixModIn, T SkewModIn)
    {
        return m_CrossFader(m_Operator1,
                            m_Operator2,
                            m_Skewer( m_PhaseGenerator(m_PhaseStep()), m_SkewModulator(m_Skew(), SkewModIn) ),
                            m_MixModulator(m_Mix(), MixModIn) );
    }

private:
    CPhaseStep<T>           m_PhaseStep;
    CPhaseGenerator<T>      m_PhaseGenerator;
    CConstGenerator<T>      m_Skew;
    CModulatorSigned<T>     m_SkewModulator;
    CPhaseSkewer<T>         m_Skewer;
    CSelectableOperator<T>  m_Operator1;
    CSelectableOperator<T>  m_Operator2;
    CConstGenerator<T>      m_Mix;
    CModulatorUnsigned<T>   m_MixModulator;
    CCrossFader<T>          m_CrossFader;
};

#endif // SKEWEDINTERPOLATINGOPERATOR_H
