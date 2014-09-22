#ifndef STEREODELAYFILTER_H
#define STEREODELAYFILTER_H

#include <vector>
#include "AudioFilterI.h"
#include "ConstNumSamplesGenerator.h"
#include "FeedbackDelay.h"

class CStereoDelayFilter : public IAudioFilter
{
public:
    CStereoDelayFilter(int SamplingFrequency);

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    void OnDelayBypass(int Index, bool Bypass);
    void OnDelayWetDry(int Index, float WetDry);
    void OnDelayMilliSeconds(int Index, float Delay);
    void OnDelayFeedback(int Index, float Feedback);

private:
    std::vector<CConstNumSamplesGenerator<float>> m_DelayTime;
    std::vector<CFeedbackDelay<float>> m_Delay;

};

#endif // STEREODELAYFILTER_H
