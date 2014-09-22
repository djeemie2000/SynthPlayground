#ifndef CNoiseFILTER_H
#define CNoiseFILTER_H

#include "AudioFilterI.h"
#include "Noise.h"

class CNoiseFilter : public IAudioFilter
{
public:
    CNoiseFilter();

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
    CNoise<float> m_Noise;
};

#endif // CNoiseFILTER_H
