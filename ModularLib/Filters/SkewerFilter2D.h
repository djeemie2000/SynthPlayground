#ifndef SKEWERFILTER_H
#define SKEWERFILTER_H

#include "AudioFilterI.h"
#include "PhaseSkewer2D.h"
#include "FilterBuffers.h"

class CPhaseSkewer2DFilter : public IAudioFilter
{
public:
    CPhaseSkewer2DFilter();

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
    CFilterBuffers<float> m_Buffers;
    CPhaseSkewer2D<float> m_Skewer;
};

#endif // SKEWERFILTER_H
