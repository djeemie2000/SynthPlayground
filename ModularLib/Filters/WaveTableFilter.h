#pragma once

#include <cstdint>
#include "AudioFilterI.h"
#include "wavetable2.h"

class CWaveTableFilter : public IAudioFilter
{
public:
    CWaveTableFilter();

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
    wt2::CWaveTableManager<std::uint8_t, float, float> m_Manager;
};
