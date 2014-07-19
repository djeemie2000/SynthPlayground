#ifndef EFFECTSAPPCONTROLLER_H
#define EFFECTSAPPCONTROLLER_H

#include "AudioFilterI.h"
#include "FeedbackDelayI.h"
#include "MasterVolumeI.h"
#include "FeedbackDelay.h"
#include "ConstGenerator.h"
#include "ConstNumSamplesGenerator.h"

class CEffectsAppController : public IAudioFilter
                                , public IFeedbackDelay
                                , public IMasterVolume
{
public:
    CEffectsAppController(int SamplingFrequency);

    int OnProcess(void *Src, void *Dst, int NumFrames, std::uint32_t TimeStamp) override;

    void OnPreGain(float PreGain);

    void OnDelayBypass(bool Bypass) override;
    void OnDelayWetDry(float WetDry) override;
    void OnDelayMilliSeconds(float Delay) override;
    void OnDelayFeedback(float Feedback) override;

    void SetMasterVolume(float Volume) override;

private:
    CConstGenerator<float> m_PreGain;
    CConstNumSamplesGenerator<float> m_DelayTime;
    CFeedbackDelay<float> m_Delay;
    CConstGenerator<float> m_MasterVolume;
};

#endif // EFFECTSAPPCONTROLLER_H
