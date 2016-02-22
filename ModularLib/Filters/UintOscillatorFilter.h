#pragma once

#include <vector>
#include "AudioFilterI.h"
#include "UintSkewedPhasor.h"
#include "FilterBuffers.h"

class CUintOscillatorFilter : public IAudioFilter
{
public:
    CUintOscillatorFilter(int SamplingFrequency);

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
    static const uisl::uint32_t Scale = 12;
    static const uisl::uint32_t InternalScale = 20;
    const int m_SamplingFrequency;
    uisl::CSkewedPhasor<Scale, InternalScale> m_Phasor;
    CFilterBuffers<float> m_Buffers;
};
