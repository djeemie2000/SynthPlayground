#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"
#include "Amp.h"

class CMixerFilter : public IAudioFilter
{
public:
    CMixerFilter(int Size);

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    void SetVolume(int Index, float Volume);
    void SetMasterVolume(float Volume);

private:
    float               m_MasterVolume;
    std::vector<float>  m_Volume;
};
