#ifndef SYNTH8CONTROLLER_H
#define SYNTH8CONTROLLER_H

#include <string>
#include <vector>
#include <cstdint>
#include "CombinedFoldedOperatorStage.h"
#include "Notes.h"
#include "OnePoleFilter.h"
#include "NonLinearShaper.h"
#include "AREnvelope.h"
#include "StepSequencer2.h"
#include "PeriodicTicker.h"
#include "SampleGrabberI.h"
#include "StepSequencerI.h"
#include "WaveFolderI.h"
#include "NoteHandlerI.h"
#include "LPFilterI.h"
#include "NonLinearShaperI.h"
#include "CombinedFoldedOperatorStageI.h"
#include "MidiHandlerI.h"
#include "LFOBankI.h"
#include "LFO.h"
#include "FeedbackDelay.h"
#include "FeedbackDelayI.h"
#include "ConstNumSamplesGenerator.h"
#include "AREnvelopeI.h"
#include "AudioSource2I.h"
#include "MasterVolumeI.h"
#include "ConstGenerator.h"

class IInt16Scope;

class CSynth8Controller
                    : public IAudioSource2
                    , public INoteHandler
                    , public ICombinedFoldedOperatorStage
                    , public IWaveFolder
                    , public ILPFilter
                    , public INonLinearShaper
                    , public IStepSequencer
                    , public IMidiHandler
                    , public ILFOBank
                    , public IFeedbackDelay
                    , public IAREnvelope
                    , public IMasterVolume
{
public:
    CSynth8Controller(int SamplingFrequency);
    ~CSynth8Controller();

    // AudioSource2
    int OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp) override;

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
    void OnFoldModAmount(int Oscillator, float Amount) override;

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
    int GetMaxNumSteps() const override;
    void SetActive(int Step, bool IsActive) override;
    void SetOctave(int Step, EOctave Octave) override;
    void SetNote(int Step, ENote Note) override;
    void SetBeatsPerMinute(int Bpm) override;
    void SetBarsPerBeat(int BarsPerBeat) override;
    void SetNumSteps(int NumSteps) override;
    void Start() override;
    void Stop() override;

    // midi input handler
    void OnNoteOn(int Note, int , std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int , std::uint32_t TimeStamp) override;
    void OnController(int, int , std::uint32_t) override;
    void OnPitchbend(int , std::uint32_t ) override;
    void OnUnknown(std::uint32_t ) override;

    // LFOs
    void SetLFOFrequency(int Idx, float Frequency) override;
    void SelectLFOWaveform(int Idx, int Selected) override;
    int LFOBankSize() const override;

    // FeedbackDelay
    void OnDelayMilliSeconds(float Delay) override;
    void OnDelayFeedback(float Feedback) override;
    void OnDelayWetDry(float WetDry) override;
    void OnDelayBypass(bool Bypass) override;

    // AREnvelope
    void OnEnvelopeAttack(float AttackMilliSeconds) override;
    void OnEnvelopeRelease(float ReleaseMilliSeconds) override;

    // MasterVolume
    void SetMasterVolume(float Volume) override;

private:
    CCombinedFoldedOperatorStage<float> m_Oscillator;
    float   m_Fold;
    CMultiStageFilter<float, COnePoleLowPassFilter<float>, 24> m_LPFilter;
    CNonLinearShaper<float> m_NonLinearShaper;
    CAREnvelope<float> m_Envelope;
    CStepSequencer2<float, 8> m_StepSequencer;
    CPeriodicTicker m_StepSequencerTicker;
    std::vector<CLFO<float>> m_LFO;
    CConstNumSamplesGenerator<float> m_NumSamplesGenerator;
    CFeedbackDelay<float> m_Delay;
    CConstGenerator<float> m_MasterVolume;
};

#endif // SYNTH8CONTROLLER_H
