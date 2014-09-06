#ifndef CCROSSMIXERFILTER_H
#define CCROSSMIXERFILTER_H

#include "AudioFilterI.h"
#include "CrossFader.h"

class CCrossMixerFilter : public IAudioFilter
{
public:
    CCrossMixerFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

private:
    CCrossFader<float> m_Mixer;
};

#endif // CCROSSMIXERFILTER_H
