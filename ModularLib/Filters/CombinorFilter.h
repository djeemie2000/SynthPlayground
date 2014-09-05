#pragma once

#include "AudioFilterI.h"
#include "SelectableCombinor.h"

class CCombinorFilter : public IAudioFilter
{
public:
    CCombinorFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    void Select(int Selected);

private:
    CSelectableCombinor<float> m_Combinor;
};
