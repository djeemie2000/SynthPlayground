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
#include "SampleGrabberI.h"
#include "StepSequencerI.h"

class IScope;

class CController : public ISampleGrabber
                    , public IStepSequencer
{
public:
    CController(IScope& Scope, int SamplingFrequency);
    ~CController();

    // AudioSource
    std::int64_t OnRead(char *Dst, std::int64_t MaxSize);//this should be some different interface?

    // SampleGrabber
    void OnGrab(int GrabSize) override;

    // NoteHandler
    void OnNoteOn(ENote Note, EOctave Octave);
    void OnNoteOff(ENote, EOctave);

    // oscillator
    void OnSync();
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

    // Step sequencer
    int NumSteps() const override;
    void SetActive(int Step, bool IsActive) override;
    void SetOctave(int Step, EOctave Octave) override;
    void SetNote(int Step, ENote Note) override;
    void SetBeatsPerMinute(int Bpm) override;
    void SetBarsPerBeat(int BarsPerBeat) override;
    void Start() override;
    void Stop() override;

private:
    typedef std::int16_t SampleValueType;
    IScope& m_Scope;

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
