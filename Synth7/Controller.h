#ifndef GRANULARSAMPLERCONTROLLER_H
#define GRANULARSAMPLERCONTROLLER_H

#include <string>
#include <vector>
#include <inttypes.h>
#include "SampleGrabber.h"
#include "Smoother.h"
#include "8BitFX.h"
#include "OscillatorStage.h"
#include "Notes.h"

class IView;

class CController
{
public:
    CController(IView& View, int SamplingFrequency);
    ~CController();

    void OnPlay();
    void OnStop();
    void OnGrab(int GrabSize);
    std::int64_t OnRead(char *Dst, std::int64_t MaxSize);//this should be some different interface?

    void OnFrequency(float Frequency);

    void OnSync();

    void OnNoteOn(ENote Note, EOctave Octave);
    void OnNoteOff(ENote, EOctave);

    void OnCombinor(const std::string& Combinor);
    void OnOperator(int Idx, const std::string& Operator);
    void OnAmplitude(int Idx, float Amplitude);
    void OnFrequencyMultiplier(int Idx, float FrequencyMultiplier);
    void OnPhaseshift(int Idx, float PhaseShift);

    // (8 bit) FX
    void OnBitCrusherDepth(int Depth);
    void OnSampleAndHoldPeriod(int Period);
    void OnRipplerStrength(int Strength);
    void OnRipplerThreshold(int Threshold);

private:
    IView& m_View;

    bool m_GrabSample;
    CSampleGrabber<std::uint8_t> m_SampleGrabber;

    COscillatorStage<float> m_Oscillator;

    C8BitFX m_Fx;
};

#endif // GRANULARSAMPLERCONTROLLER_H
