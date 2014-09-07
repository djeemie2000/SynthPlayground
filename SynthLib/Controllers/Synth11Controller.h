#ifndef Synth11CONTROLLER_H
#define Synth11CONTROLLER_H

#include <string>
#include <vector>
#include <cstdint>
#include "Notes.h"
#include "OnePoleFilter.h"
#include "AREnvelope.h"
#include "PeriodicTicker.h"
#include "NoteHandlerI.h"
#include "LPFilterI.h"
#include "MidiInputHandlerI.h"
#include "LFO.h"
#include "FeedbackDelay.h"
#include "FeedbackDelayI.h"
#include "ConstNumSamplesGenerator.h"
#include "AREnvelopeI.h"
#include "AudioSource2I.h"
#include "MasterVolumeI.h"
#include "ConstGenerator.h"
#include "SkewedInterpolatingOperator.h"
#include "IntegerPowerShaper.h"
#include "PowerLawDistortion.h"
#include "Modulator.h"
#include "ADSREnvelope.h"
#include "PosNegShaper.h"

class CSynth11Controller
                    : public IAudioSource2
                    , public INoteHandler
                    , public ILPFilter
                    , public IMidiInputHandler
{
public:
    CSynth11Controller(int SamplingFrequency);
    ~CSynth11Controller();

    // AudioSource2
    int OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp) override;

    // NoteHandler
    void OnNoteOn(ENote Note, EOctave Octave) override;
    void OnNoteOff(ENote, EOctave) override;

    //  operator
    void SelectOperator1(int Selected);
    void SelectOperator2(int Selected);
    void SetMix(float Mix);
    void SetMixModAmt(float ModAmt);
    void SetSkew(float Skew);
    void SetSkewModAmt(float ModAmt);

    // Shaper
    void SetShaperStrength(float Strength);
    void SetShaperPower(int Power);
    void SetShaperPreGain(float PreGain);

    // PosNeg shaping
    void SetInverterMode(int Mode);
    void SetDerectifierMode(int Mode);

    // WaveFolder
    void OnWaveFold(float Fold);

    // LP filter
    void OnLPFilterCutoff(float Parameter) override;
    void OnLPFilterPoles(int Stages) override;
    void OnLPFilterFeedback(float Feedback) override;

    // midi input handler
    void OnNoteOn(int Note, int , std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int , std::uint32_t TimeStamp) override;
    void OnController(int, int , std::uint32_t) override;
    void OnPitchbend(int , std::uint32_t) override;
    void OnUnknown(std::uint32_t ) override;

    // Envelope
    void OnEnvelopeAttack(int Idx, float AttackMilliSeconds);
    void OnEnvelopeDecay(int Idx, float DecayMilliSeconds);
    void OnEnvelopeSustain(int Idx, float Sustain);
    void OnEnvelopeRelease(int Idx, float ReleaseMilliSeconds);

    // LFOs
    void SetLFOFrequency(int Idx, float Frequency);
    void SelectLFOWaveform(int Idx, int Selected);
    int LFOBankSize() const;

    // Modulation
    void OnModAmount(int Modulator, float ModAmt);

    // distortion
    void OnDistortionDrive(float Drive);

    // AREnvelope
    void OnEnvelopeAttack(float AttackMilliSeconds);
    void OnEnvelopeRelease(float ReleaseMilliSeconds);

    // MasterVolume
    void SetMasterVolume(float Volume);

private:
    CSkewedInterpolatingOperator<float> m_Oscillator;
    CIntegerPowerShaper<float> m_Shaper;
    CPosNegInverter<float> m_Inverter;
    CPosNegDerectifier<float> m_Derectifier;
    CConstGenerator<float> m_Fold;
    CConstGenerator<float> m_LPFilterCutoff;
    CMultiStageFilter<float, COnePoleLowPassFilter<float>, 24> m_LPFilter;

    CConstNumSamplesGenerator<float> m_NumSamplesGenerator;
    CAREnvelope<float>      m_AREnvelope;
    std::vector<CADSREnvelope<float>> m_Envelope;
    std::vector<CLFO<float>> m_LFO;
    std::vector<CModulatorSigned<float>> m_Modulator;

    CPowerLawDistortion<float> m_Distortion;
    CConstGenerator<float> m_MasterVolume;
};

#endif // Synth11CONTROLLER_H
