#ifndef DelayLineFILTER_H
#define DelayLineFILTER_H

#include <vector>
#include "AudioFilterI.h"
#include "ConstNumSamplesGenerator.h"
#include "DelayLine2.h"

class CDelayLineFilter : public IAudioFilter
{
public:
    CDelayLineFilter(int SamplingFrequency);

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

    void SetDelayRange(int DelayRangeMilliSeconds);
    int GetMaxDelayMilliSeconds() const;

private:
    CConstNumSamplesGenerator<int> m_DelayRange;
    CDelayLine2<float> m_DelayLine;

};

#endif // DelayLineFILTER_H
