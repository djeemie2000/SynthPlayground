#pragma once

#include "AudioFilterI.h"
#include "CombinedOperator.h"
#include "FilterBuffers.h"

class CCombinedOperatorFilter : public IAudioFilter
{
public:
    CCombinedOperatorFilter(int SamplingFrequency);

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

    void SelectOperatorA(int Selected);
    void SelectOperatorB(int Selected);
    void SelectCombinor(int Selected);

private:
    CFilterBuffers<float> m_Buffers;
    CCombinedOperator<float> m_CombinedOperator;
};
