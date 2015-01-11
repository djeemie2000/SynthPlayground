#ifndef UnipolarLimiterFILTER_H
#define UnipolarLimiterFILTER_H

#include "AudioFilterI.h"
#include "Limiter.h"

class CUnipolarLimiterFilter : public IAudioFilter
{
public:
    CUnipolarLimiterFilter();

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
    CFixedLimiter<float, 0, 1> m_Limiter;
};

#endif // UnipolarLimiterFILTER_H
