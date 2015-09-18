#pragma once

#include <vector>
#include "AudioFilterI.h"
#include "IntSimpleOscillator.h"
#include "FilterBuffers.h"

class CIntSimpleOscillatorFilter : public IAudioFilter
{
public:
    CIntSimpleOscillatorFilter(int SamplingFrequency);

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

    void SelectWaveform(int Selection);

private:
    static const int Scale = 12;
    isl::CSimpleOscillator<Scale> m_Oscillator;
    CFilterBuffers<float> m_Buffers;
};
