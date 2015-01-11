#ifndef LimiterFILTER_H
#define LimiterFILTER_H

#include "AudioFilterI.h"
#include "Limiter.h"

class CLimiterFilter : public IAudioFilter
{
public:
    CLimiterFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  const std::vector<std::shared_ptr<IMidiHandler>> MidiHandlers,
                  int NumFrames,
                  std::uint32_t TimeStLimiter) override;

private:
    CLimiter<float> m_Limiter;
};

#endif // LimiterFILTER_H
