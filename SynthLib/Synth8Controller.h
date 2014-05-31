#ifndef SYNTH8CONTROLLER_H
#define SYNTH8CONTROLLER_H

#include <string>
#include <vector>
#include <cstdint>
#include "SampleGrabber.h"
#include "Smoother.h"
#include "CombinedFoldedOperatorStage.h"
#include "Notes.h"
#include "OnePoleFilter.h"
#include "NonLinearShaper.h"
#include "BasicEnvelope.h"
#include "StepSequencer2.h"
#include "PeriodicTicker.h"
#include "SampleGrabberI.h"
#include "StepSequencerI.h"
#include "WaveFolderI.h"
#include "NoteHandlerI.h"
#include "LPFilterI.h"
#include "NonLinearShaperI.h"
#include "CombinedFoldedOperatorStageI.h"
#include "AudioSourceI.h"
#include "MidiInputHandlerI.h"

class IScope;

class CSynth8Controller
                    : public IAudioSource
                    , public ISampleGrabber
                    , public INoteHandler
                    , public ICombinedFoldedOperatorStage
                    , public IWaveFolder
                    , public ILPFilter
                    , public INonLinearShaper
                    , public IStepSequencer
                    , public IMidiInputHandler
{
public:
    CSynth8Controller(IScope& Scope, int SamplingFrequency);
    ~CSynth8Controller();

    // AudioSource
    std::int64_t OnRead(char *Dst, std::int64_t MaxSize) override;

    // SampleGrabber
    void OnGrab(int GrabSize) override;

    // NoteHandler
    void OnNoteOn(ENote Note, EOctave Octave) override;
    void OnNoteOff(ENote, EOctave) override;

    // oscillator
    void OnSync() override;
    void OnCombinor(int Selected) override;
    void OnOperator(int Idx, int Selected) override;
    void OnAmplitude(int Idx, float Amplitude) override;
    void OnFrequencyMultiplier(int Idx, float FrequencyMultiplier) override;
    void OnPhaseshift(int Idx, float PhaseShift) override;
    void OnFold(int Idx, float Fold) override;

    // WaveFolder
    void OnWaveFold(float Fold) override;

    // LP filter
    void OnLPFilterCutoff(float Parameter) override;
    void OnLPFilterPoles(int Stages) override;
    void OnLPFilterFeedback(float Feedback) override;

    // nonlinear shaper
    void OnNonLinearShaperA(float A) override;
    void OnNonLinearShaperB(float B) override;
    void OnNonLinearShaperPreGain(float PreGain) override;

    // Step sequencer
    int NumSteps() const override;
    void SetActive(int Step, bool IsActive) override;
    void SetOctave(int Step, EOctave Octave) override;
    void SetNote(int Step, ENote Note) override;
    void SetBeatsPerMinute(int Bpm) override;
    void SetBarsPerBeat(int BarsPerBeat) override;
    void Start() override;
    void Stop() override;

    // midi input handler
    void OnNoteOn(int Note, int ) override;
    void OnNoteOff(int Note, int ) override;
    void OnController(int, int ) override;
    void OnPitchbend(int) override;
    void OnUnknown() override;

private:
    typedef std::int16_t SampleValueType;
    IScope& m_Scope;

    bool m_GrabSample;
    CSampleGrabber<SampleValueType> m_SampleGrabber;

    CCombinedFoldedOperatorStage<float> m_Oscillator;
    float   m_Fold;
    CMultiStageFilter<float, COnePoleLowPassFilter<float>, 24> m_LPFilter;
    CNonLinearShaper<float> m_NonLinearShaper;
    CBasicEnvelope<float> m_Envelope;
    CStepSequencer2<float, 8> m_StepSequencer;
    CPeriodicTicker m_StepSequencerTicker;
};

#endif // SYNTH8CONTROLLER_H
