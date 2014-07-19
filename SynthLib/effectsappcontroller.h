#ifndef EFFECTSAPPCONTROLLER_H
#define EFFECTSAPPCONTROLLER_H

#include "AudioFilterI.h"
#include "MasterVolumeI.h"
#include "FeedbackDelay.h"
#include "ConstGenerator.h"
#include "ConstNumSamplesGenerator.h"

class CEffectsAppController : public IAudioFilter
                                , public IMasterVolume
{
public:
    CEffectsAppController(int SamplingFrequency);

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers, const std::vector<void*>& DestinationBuffers, int NumFrames, std::uint32_t TimeStamp);

    void OnPreGain(float PreGain);

    void OnDelayBypassLeft(bool Bypass);
    void OnDelayWetDryLeft(float WetDry);
    void OnDelayMilliSecondsLeft(float Delay);
    void OnDelayFeedbackLeft(float Feedback);

    void OnDelayBypassRight(bool Bypass);
    void OnDelayWetDryRight(float WetDry);
    void OnDelayMilliSecondsRight(float Delay);
    void OnDelayFeedbackRight(float Feedback);

    void SetMasterVolume(float Volume) override;

private:
    CConstGenerator<float> m_PreGain;
    CConstNumSamplesGenerator<float> m_DelayTimeLeft;
    CFeedbackDelay<float> m_DelayLeft;
    CConstNumSamplesGenerator<float> m_DelayTimeRight;
    CFeedbackDelay<float> m_DelayRight;
    CConstGenerator<float> m_MasterVolume;
};

#endif // EFFECTSAPPCONTROLLER_H
