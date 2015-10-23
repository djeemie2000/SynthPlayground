#pragma once

#include "AudioFilterI.h"
#include "IntSkewer2D.h"
#include "FilterBuffers.h"

class CIntSkewer2DFilter : public IAudioFilter
{
public:
    CIntSkewer2DFilter();

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
    CFilterBuffers<float> m_Buffers;
    isl::CPhaseSkewer2D<int> m_Skewer;
};
