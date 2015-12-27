#pragma once

#include "AudioFilterI.h"
#include "FourPoleFilter.h"

class CLpf4PoleFilter : public IAudioFilter
{
public:
    CLpf4PoleFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  const std::vector<std::shared_ptr<IMidiHandler>> MidiHandlers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    void SetPoles(int Poles);
    void SetResonance(float Resonance);

private:
    CFourPoleLowPassFilter<float> m_LPFilter;
};
