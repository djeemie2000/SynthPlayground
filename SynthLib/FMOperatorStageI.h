#ifndef FMOPERATORSTAGEI_H
#define FMOPERATORSTAGEI_H

class IFMOperatorStage
{
public:
    virtual ~IFMOperatorStage(){}

    virtual void OnSync() =0;
    virtual void OnCarrier(int Selected) =0;
    virtual void OnModulator(int Selected) =0;
    virtual void OnOscillator(int Selected) =0;
    virtual void OnModulatorAmplitude(float Amplitude) =0;
    virtual void OnModulatorAmplitudeModAmount(float ModAmt) =0;
    virtual void OnModulatorFrequencyMultiplier(float FrequencyMultiplier) =0;
    virtual void OnModulatorPhaseshift(float PhaseShift) =0;

};

#endif // FMOPERATORSTAGEI_H
