#ifndef DelayVerbFILTER_H
#define DelayVerbFILTER_H

#include <vector>
#include "AudioFilterI.h"
#include "ConstNumSamplesGenerator.h"
#include "delayverb.h"
#include "FilterBuffers.h"

class CDelayVerbFilter : public IAudioFilter
{
public:
    CDelayVerbFilter(int SamplingFrequency);

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
    int m_DelayRange;
    CDelayVerb<float> m_DelayVerb;
    CFilterBuffers<float> m_Buffers;
};

#endif // DelayVerbFILTER_H
