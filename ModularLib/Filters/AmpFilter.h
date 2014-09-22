#ifndef AMPFILTER_H
#define AMPFILTER_H

#include "AudioFilterI.h"
#include "Amp.h"

class CAmpFilter : public IAudioFilter
{
public:
    CAmpFilter();

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
    CAmp<float> m_Amp;
};

#endif // AMPFILTER_H
