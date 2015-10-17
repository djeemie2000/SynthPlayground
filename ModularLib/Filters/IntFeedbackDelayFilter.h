#pragma once

#include <vector>
#include "AudioFilterI.h"
#include "IntFeedbackDelay.h"
#include "FilterBuffers.h"

class CIntFeedbackDelayFilter : public IAudioFilter
{
public:
    CIntFeedbackDelayFilter(int SamplingFrequency);

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
    static const int Scale = 12;
    static const int Capacity = 44100;
    isl::CFeedbackDelay<int, Capacity> m_FeedbackDelay;
    CFilterBuffers<float> m_Buffers;
};
