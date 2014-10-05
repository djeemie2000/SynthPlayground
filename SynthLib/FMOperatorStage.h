#ifndef FMOPERATORSTAGE_H
#define FMOPERATORSTAGE_H

#include "SelectableOperator.h"
#include "PhaseStep.h"
#include "PhaseGenerator.h"
#include "Conversions.h"// limit

template<class T>
class CFMOperatorStage
{
public:
    CFMOperatorStage(T SamplingFrequency, const CSelectableOperator<T>& Operator)
     : m_CarrierPhaseStep(SamplingFrequency)
     , m_CarrierPhaseGen()
     , m_Carrier(Operator)
     , m_Frequency(440)
     , m_ModulatorPhaseStep(SamplingFrequency)
     , m_ModulatorPhaseGen()
     , m_Modulator(Operator)
     , m_ModulatorAmplitude(0)
     , m_ModulatorFreqMultiplier(1)
     , m_ModulatorAmplitudeModAmt(0)
     , m_ModulatorPhaseShift(0)
     , m_Oscillator(Operator)
    {
        m_Carrier.Select(0);
        m_Modulator.Select(0);
        m_Oscillator.Select(0);

        SetFrequency(440.0f);
    }

    void SetFrequency(T Frequency)
    {
        m_Frequency = Frequency;

        m_CarrierPhaseStep.SetFrequency(m_Frequency);
        m_ModulatorPhaseStep.SetFrequency(m_Frequency*m_ModulatorFreqMultiplier);
    }

    void SelectCarrier(int Selected)
    {
        m_Carrier.Select(Selected);
    }

    void SelectModulator(int Selected)
    {
        m_Modulator.Select(Selected);
    }

    void SelectOscillator(int Selected)
    {
        m_Oscillator.Select(Selected);
    }

    void SetModulatorAmplitude(T Amplitude)
    {
        m_ModulatorAmplitude = Amplitude;
    }

    void SetModulatorFrequencyMultiplier(T Multiplier)
    {
        m_ModulatorFreqMultiplier = Multiplier;

        m_CarrierPhaseStep.SetFrequency(m_Frequency);
        m_ModulatorPhaseStep.SetFrequency(m_Frequency*m_ModulatorFreqMultiplier);
    }

    void SetModulatorAmplitudeModAmount(T ModAmt)
    {
        m_ModulatorAmplitudeModAmt = ModAmt;
    }

    void SetModulatorPhaseshift(T PhaseShift)
    {
        m_ModulatorPhaseShift = PhaseShift;
    }

    void Sync()
    {
        // should set to -1 now instead of 0 ?
        m_CarrierPhaseGen.Sync();
        m_ModulatorPhaseGen.Sync(m_ModulatorPhaseShift);
    }

    T operator()()
    {
        T Phase = m_Carrier(m_CarrierPhaseGen()) + m_ModulatorAmplitude*m_Modulator(m_ModulatorPhaseGen());
        // we can hard limit the phase or the oscillator output.
        // which one sounds most interesting?
        return m_Oscillator(HardLimitSigned(Phase));
    }

    T operator()(T ModIn)
    {
        T ModulatorAmplitude = m_ModulatorAmplitude + m_ModulatorAmplitudeModAmt*ModIn;
        T Phase = m_Carrier(m_CarrierPhaseGen(m_CarrierPhaseStep())) + ModulatorAmplitude*m_Modulator(m_ModulatorPhaseGen(m_ModulatorPhaseStep()));
        // we can hard limit the modulator amplitude, the phase or the oscillator output.
        // which one sounds most interesting?
        return m_Oscillator(HardLimitSigned(Phase));
    }

private:
    CPhaseStep<T> m_CarrierPhaseStep;
    CPhaseAccumulator<T> m_CarrierPhaseGen;
    CSelectableOperator<T> m_Carrier;
    T m_Frequency;

    CPhaseStep<T> m_ModulatorPhaseStep;
    CPhaseAccumulator<T> m_ModulatorPhaseGen;
    CSelectableOperator<T> m_Modulator;
    T m_ModulatorAmplitude;
    T m_ModulatorFreqMultiplier;
    T m_ModulatorAmplitudeModAmt;
    T m_ModulatorPhaseShift;

    CSelectableOperator<T> m_Oscillator;
};

#endif // FMOPERATORSTAGE_H
