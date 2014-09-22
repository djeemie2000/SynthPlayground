#ifndef SKEWERFILTER_H
#define SKEWERFILTER_H

#include "AudioFilterI.h"
#include "PhaseSkewer.h"

class CPhaseSkewerFilter : public IAudioFilter
{
public:
    CPhaseSkewerFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

private:
    CPhaseSkewer<float> m_Skewer;
};

#endif // SKEWERFILTER_H
