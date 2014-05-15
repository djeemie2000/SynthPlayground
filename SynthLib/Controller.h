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
#include "BasicEnvelope.h"
#include "StepSequencer2.h"
#include "PeriodicTicker.h"

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

    // WaveFolder
    void OnWaveFold(float Fold);

    // LP filter
    void OnLPFilterParameter(float Parameter);
    void OnLPFilterStages(int Stages);
    void OnLPFilterFeedback(float Feedback);

    // nonlinear shaper
    void OnNonLinearShaperA(float A);
    void OnNonLinearShaperB(float B);
    void OnNonLinearShaperPreGain(float PreGain);

    // (8 bit) FX
    void OnBitCrusherDepth(int Depth);
    void OnSampleAndHoldPeriod(int Period);
    void OnRipplerStrength(int Strength);
    void OnRipplerThreshold(int Threshold);

    // Step sequencer
    int NumSteps() const;

    void SetActive(int Step, bool IsActive);
    void SetOctave(int Step, EOctave Octave);
    void SetNote(int Step, ENote Note);

    void SetBeatsPerMinute(int Bpm);
    void SetBarsPerBeat(int BarsPerBeat);

    void Start();
    void Stop();


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
    CBasicEnvelope<float> m_Envelope;
    CStepSequencer2<float, 8> m_StepSequencer;
    CPeriodicTicker m_StepSequencerTicker;
};

#endif // GRANULARSAMPLERCONTROLLER_H
