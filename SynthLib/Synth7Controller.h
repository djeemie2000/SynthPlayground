#ifndef SYNTH7CONTROLLER_H
#define SYNTH7CONTROLLER_H

#include <string>
#include <vector>
#include <cstdint>
#include "SampleGrabber.h"
#include "Smoother.h"
#include "8BitFX.h"
#include "CombinedOperatorStage.h"
#include "Notes.h"
#include "OnePoleFilter.h"
#include "NonLinearShaper.h"
#include "BasicEnvelope.h"
#include "StepSequencer2.h"
#include "PeriodicTicker.h"
#include "SampleGrabberI.h"
#include "StepSequencerI.h"
#include "BitFxI.h"
#include "WaveFolderI.h"
#include "NoteHandlerI.h"
#include "LPFilterI.h"
#include "NonLinearShaperI.h"
#include "CombinedOperatorStageI.h"
#include "AudioSourceI.h"
#include "MidiInputHandlerI.h"

class IInt16Scope;

class CSynth7Controller
                    : public IAudioSource
                    , public ISampleGrabber
                    , public INoteHandler
                    , public ICombinedOperatorStage
                    , public IWaveFolder
                    , public ILPFilter
                    , public INonLinearShaper
                    , public IBitFx
                    , public IStepSequencer
                    , public IMidiInputHandler
{
public:
    CSynth7Controller(IInt16Scope& Scope, int SamplingFrequency);
    ~CSynth7Controller();

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

    // (8 bit) FX
    void OnBitCrusherDepth(int Depth) override;
    void OnSampleAndHoldPeriod(int Period) override;
    void OnRipplerStrength(int Strength) override;

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
    IInt16Scope& m_Scope;

    bool m_GrabSample;
    CSampleGrabber<SampleValueType> m_SampleGrabber;

    CCombinedOperatorStage<float> m_Oscillator;
    float   m_Fold;
    C16BitsSignedFX m_Fx;
    CMultiStageFilter<float, COnePoleLowPassFilter<float>, 24> m_LPFilter;
    CNonLinearShaper<float> m_NonLinearShaper;
    CBasicEnvelope<float> m_Envelope;
    CStepSequencer2<float, 8> m_StepSequencer;
    CPeriodicTicker m_StepSequencerTicker;
};

#endif // SYNTH7CONTROLLER_H
