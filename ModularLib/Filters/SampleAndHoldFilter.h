#ifndef CSampleAndHoldFILTER_H
#define CSampleAndHoldFILTER_H

#include "AudioFilterI.h"
#include "SampleAndHold.h"

class CSampleAndHoldFilter : public IAudioFilter
{
public:
    CSampleAndHoldFilter();

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
    CSampleAndHold<float> m_SampleAndHold;
};

#endif // CSampleAndHoldFILTER_H
