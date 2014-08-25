#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"

class CConstFilter : public IAudioFilter
{
public:
    CConstFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    void Set(float Value);
private:
    float               m_Value;
};
