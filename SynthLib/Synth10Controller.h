#ifndef SYNTH10CONTROLLER_H
#define SYNTH10CONTROLLER_H

#include <string>
#include <vector>
#include <cstdint>
#include "Notes.h"
#include "OnePoleFilter.h"
#include "AREnvelope.h"
#include "StepSequencer2.h"
#include "PeriodicTicker.h"
#include "StepSequencerI.h"
#include "NoteHandlerI.h"
#include "LPFilterI.h"
#include "MidiInputHandlerI.h"
#include "LFOBankI.h"
#include "LFO.h"
#include "FeedbackDelay.h"
#include "FeedbackDelayI.h"
#include "ConstNumSamplesGenerator.h"
#include "AREnvelopeI.h"
#include "AudioSource2I.h"
#include "MasterVolumeI.h"
#include "ConstGenerator.h"
#include "SkewedInterpolatingOperator.h"
#include "InterpolatingOperatorI.h"
#include "DCOperator.h"
#include "IntegerPowerShaper.h"

class CSynth10Controller
                    : public IAudioSource2
                    , public INoteHandler
                    , public IInterpolatingOperator
                    , public ILPFilter
                    , public IStepSequencer
                    , public IMidiInputHandler
                    , public ILFOBank
                    , public IFeedbackDelay
                    , public IAREnvelope
                    , public IMasterVolume
{
public:
    CSynth10Controller(int SamplingFrequency);
    ~CSynth10Controller();

    // AudioSource2
    int OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp) override;

    // NoteHandler
    void OnNoteOn(ENote Note, EOctave Octave) override;
    void OnNoteOff(ENote, EOctave) override;

    //  operator
    void SelectOperator1(int Selected) override;
    void SelectOperator2(int Selected) override;
    void SetMix(float Mix) override;
    void SetMixModAmt(float ModAmt) override;

    void SetSkew(float Skew);
    void SetSkewModAmt(float ModAmt);

    // Shaper
    void SetShaperStrength(float Strength);
    void SetShaperPower(int Power);
    void SetShaperPreGain(float PreGain);

    // DC
    void SetDCOffset(float DCOffset);
    void SetDCOffsetModAmt(float ModAmt);

    // LP filter
    void OnLPFilterCutoff(float Parameter) override;
    void OnLPFilterPoles(int Stages) override;
    void OnLPFilterFeedback(float Feedback) override;

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
    void OnNoteOn(int Note, int , std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int , std::uint32_t TimeStamp) override;
    void OnController(int, int , std::uint32_t) override;
    void OnPitchbend(int , std::uint32_t) override;
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
    CSkewedInterpolatingOperator<float> m_Oscillator;
    CIntegerPowerShaper<float> m_Shaper;
    CConstGenerator<float>  m_DCOffset;
    CModulatorSigned<float>     m_DCOffsetModulator;
    CFixedGainDCOperator<float> m_DCOperator;
    CMultiStageFilter<float, COnePoleLowPassFilter<float>, 24> m_LPFilter;
    CAREnvelope<float>      m_Envelope;

    std::vector<CLFO<float>> m_LFO;

    CStepSequencer2<float, 8> m_StepSequencer;
    CPeriodicTicker m_StepSequencerTicker;

    CConstNumSamplesGenerator<float> m_NumSamplesGenerator;
    CFeedbackDelay<float> m_Delay;
    CConstGenerator<float> m_MasterVolume;
};

#endif // SYNTH10CONTROLLER_H
