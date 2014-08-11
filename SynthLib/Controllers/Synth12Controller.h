#ifndef SYNTH12CONTROLLER_H
#define SYNTH12CONTROLLER_H

#include "MidiInputHandlerI.h"
#include "WaveTable.h"
#include "PhaseGenerator.h"
#include "AudioSource2I.h"
#include "OnePoleFilter.h"
#include "WaveFolder.h"
#include "ConstGenerator.h"
#include "BasicEnvelope.h"

class CSynth12Controller : public IAudioSource2,
                            public IMidiInputHandler
{
public:
    CSynth12Controller(int SamplingFrequency);

    // AudioSource2
    int OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp) override;

    // IMidiInputHandler
    void OnNoteOn(int Note, int , std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int , std::uint32_t TimeStamp) override;
    void OnController(int, int , std::uint32_t) override;
    void OnPitchbend(int , std::uint32_t) override;
    void OnUnknown(std::uint32_t ) override;

    // oscillator/operator
    void OpenCarrierWaveTable(const std::string& Path);
    void OnCarrierPlaybackSpeed(float Speed);
    //TODO modulator

    // WaveFolder
    void OnWaveFold(float Fold);

    // LP filter
    void OnLPFilterCutoff(float Parameter);
    void OnLPFilterPoles(int Stages);
    void OnLPFilterFeedback(float Feedback);

    // MasterVolume
    void SetMasterVolume(float Volume);


private:
    CWaveTable<float, float> m_CarrierWaveTable;
    CWaveTablePhaseStep<float> m_CarrierPhaseStep;
    CPhaseGenerator<float, 0, 1> m_CarrierPhase;

    CBasicEnvelope<float> m_Envelope;

    CConstGenerator<float> m_Fold;
    CConstGenerator<float> m_LPFilterCutoff;
    CMultiStageFilter<float, COnePoleLowPassFilter<float>, 24> m_LPFilter;

    CConstGenerator<float> m_MasterVolume;
};

#endif // SYNTH12CONTROLLER_H
