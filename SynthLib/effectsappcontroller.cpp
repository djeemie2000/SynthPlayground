#include "effectsappcontroller.h"

CEffectsAppController::CEffectsAppController(int SamplingFrequency)
 : m_PreGain()
 , m_DelayTime(SamplingFrequency)
 , m_Delay(5*SamplingFrequency, 0)// max delay is 5 seconds
 , m_MasterVolume()
{
    m_PreGain.Set(1.0);
    m_DelayTime.SetMilliSeconds(250);
    m_Delay.SetDelay(m_DelayTime());
    m_MasterVolume.Set(0.5);
}

int CEffectsAppController::OnProcess(void *Src, void *Dst, int NumFrames, std::uint32_t /*TimeStamp*/)
{
    const float* pSrc = (const float*)Src;
    const float* pSrcEnd = pSrc + NumFrames;
    float* pDst = (float*)Dst;
    while(pSrc<pSrcEnd)
    {
        *pDst =  m_MasterVolume()*m_Delay(m_PreGain()*(*pSrc));
        ++pSrc;
        ++pDst;
    }

    return 0;
}

void CEffectsAppController::OnPreGain(float PreGain)
{
    m_PreGain.Set(PreGain);
}

void CEffectsAppController::OnDelayBypass(bool Bypass)
{
    m_Delay.SetBypass(Bypass);
}

void CEffectsAppController::OnDelayWetDry(float WetDry)
{
    m_Delay.SetWet(WetDry);
}

void CEffectsAppController::OnDelayMilliSeconds(float Delay)
{
    m_DelayTime.SetMilliSeconds(Delay);
    m_Delay.SetDelay(m_DelayTime());
}

void CEffectsAppController::OnDelayFeedback(float Feedback)
{
    m_Delay.SetFeedback(Feedback);
}

void CEffectsAppController::SetMasterVolume(float Volume)
{
    m_MasterVolume.Set(Volume);
}
