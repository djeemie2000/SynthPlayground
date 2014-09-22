#pragma once

#include "AudioFilterI.h"
#include "PhaseStep.h"
#include "SimpleOscillator.h"

class CSimpleOscillatorFilter : public IAudioFilter
{
public:
    CSimpleOscillatorFilter(int SamplingFrequency);

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    void SelectWaveform(int Selection);

private:
    CSimpleOscillator<float> m_Oscillator;
};
