#ifndef GRANULARSAMPLERCONTROLLER_H
#define GRANULARSAMPLERCONTROLLER_H

#include <string>
#include <vector>
#include <cstdint>
#include "SampleGrabber.h"
#include "Smoother.h"
#include "8BitFX.h"
#include "OscillatorStage.h"
#include "Notes.h"
#include "OnePoleFilter.h"
#include "NonLinearShaper.h"

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

    void OnNoteOn(ENote Note, EOctave Octave);
    void OnNoteOff(ENote, EOctave);
    void OnSync();

    // oscillator
    void OnCombinor(int Selected);
    void OnOperator(int Idx, int Selected);
    void OnAmplitude(int Idx, float Amplitude);
    void OnFrequencyMultiplier(int Idx, float FrequencyMultiplier);
    void OnPhaseshift(int Idx, float PhaseShift);

    //
    void OnWaveFold(float Fold);
    void OnLPFilterParameter(float Parameter);
    void OnLPFilterStages(int Stages);
    void OnLPFilterFeedback(float Feedback);

    //
    void OnNonLinearShaperA(float A);
    void OnNonLinearShaperB(float B);
    void OnLinearShaperPreGain(float PreGain);

    // (8 bit) FX
    void OnBitCrusherDepth(int Depth);
    void OnSampleAndHoldPeriod(int Period);
    void OnRipplerStrength(int Strength);
    void OnRipplerThreshold(int Threshold);

private:
    typedef std::int16_t SampleValueType;
    IView& m_View;

    bool m_GrabSample;
    CSampleGrabber<SampleValueType> m_SampleGrabber;

    COscillatorStage<float> m_Oscillator;
    float   m_Fold;
    C16BitsSignedFX m_Fx;
    CMultiStageFilter<float, COnePoleLowPassFilter<float>, 24> m_LPFilter;
    CNonLinearShaper<float> m_NonLinearShaper;
};

#endif // GRANULARSAMPLERCONTROLLER_H
