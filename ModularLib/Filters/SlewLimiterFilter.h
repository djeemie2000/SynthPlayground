#ifndef SlewLimiterFILTER_H
#define SlewLimiterFILTER_H

#include "AudioFilterI.h"
#include "SlewLimiter.h"

class CSlewLimiterFilter : public IAudioFilter
{
public:
    CSlewLimiterFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  const std::vector<std::shared_ptr<IMidiHandler>> MidiHandlers,
                  int NumFrames,
                  std::uint32_t TimeStSlewLimiter) override;

private:
    CSlewLimiter<float> m_SlewLimiter;
};

#endif // SlewLimiterFILTER_H
