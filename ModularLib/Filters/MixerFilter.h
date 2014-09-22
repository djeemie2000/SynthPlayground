#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"

class CMixerFilter : public IAudioFilter
{
public:
    CMixerFilter(int Size);

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

    void SetVolume(int Index, float Volume);
    void SetMasterVolume(float Volume);

private:
    float               m_MasterVolume;
    std::vector<float>  m_Volume;
};
