#ifndef FMFREQUENCYMODULATOR_H
#define FMFREQUENCYMODULATOR_H

#include "SimpleOscillator.h"

template<class T>
class CFMFrequencyModulator
{
public:
    CFMFrequencyModulator(T SamplingFrequency)
        : m_Modulator(SamplingFrequency)
    {
        m_Modulator.SelectWaveform(3);//full pseudo sin waveform
    }

    void SelectModulatorWaveform(int Selection)
    {
        m_Modulator.SelectWaveform(Selection);
    }

    void Sync()
    {
        m_Modulator.Sync();
    }

    T operator()(T CarrierFrequency, T ModulatorAmplitude, T ModulationFrequencyMultiplier)
    {
        // FM freq modulation. The modulator uses the carrier frequency as a base for its frequency.
        return CarrierFrequency*(1 + m_Modulator(CarrierFrequency*ModulationFrequencyMultiplier)*ModulatorAmplitude);
    }

private:
    CSimpleOscillator<T> m_Modulator;
};

#endif // FMFREQUENCYMODULATOR_H
