#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"
#include "FilterBuffers.h"

class CChebishevFilter : public IAudioFilter
{
public:
    CChebishevFilter();

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

private:
    static const int Size = 6;
    CFilterBuffers<float> m_Buffers;
};
