#include "EffectsAppController.h"

CEffectsAppController::CEffectsAppController(int SamplingFrequency)
 : m_PreGain()
 , m_DelayTimeLeft(SamplingFrequency)
 , m_DelayLeft(5*SamplingFrequency, 0)// max delay is 5 seconds
 , m_DelayTimeRight(SamplingFrequency)
 , m_DelayRight(5*SamplingFrequency, 0)
 , m_MasterVolume()
{
    m_PreGain.Set(1.0);
    m_DelayTimeLeft.SetMilliSeconds(250);
    m_DelayLeft.SetDelay(m_DelayTimeLeft());
    m_DelayTimeRight.SetMilliSeconds(250);
    m_DelayRight.SetDelay(m_DelayTimeRight());
    m_MasterVolume.Set(0.5);
}

std::vector<std::string> CEffectsAppController::GetInputNames() const
{
    return {"InL", "InR"};
}

std::vector<std::string> CEffectsAppController::GetOutputNames() const
{
    return {"OutL", "OutR"};
}

std::vector<std::string> CEffectsAppController::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CEffectsAppController::GetMidiOutputNames() const
{
    return {};
}

int CEffectsAppController::OnProcess(const std::vector<void*>& SourceBuffers,
                                     const std::vector<void*>& DestinationBuffers,
                                     const std::vector<std::shared_ptr<IMidiRenderer> > /*MidiRenderers*/,
                                     int NumFrames,
                                     std::uint32_t /*TimeStamp*/)
{
    if(SourceBuffers[0] && DestinationBuffers[0])
    {
        const float* pSrcL = (const float*)SourceBuffers[0];
        const float* pSrcEndL = pSrcL + NumFrames;
        float* pDstL = (float*)DestinationBuffers[0];
        while(pSrcL<pSrcEndL)
        {
            *pDstL =  m_MasterVolume()*m_DelayLeft(m_PreGain()*(*pSrcL));
            ++pSrcL;
            ++pDstL;
        }
    }

    if(SourceBuffers[1] && DestinationBuffers[1])
    {
        const float* pSrcR = (const float*)SourceBuffers[1];
        const float* pSrcEndR = pSrcR + NumFrames;
        float* pDstR = (float*)DestinationBuffers[1];
        while(pSrcR<pSrcEndR)
        {
            *pDstR =  m_MasterVolume()*m_DelayRight(m_PreGain()*(*pSrcR));
            ++pSrcR;
            ++pDstR;
        }
    }

    return 0;
}

void CEffectsAppController::OnPreGain(float PreGain)
{
    m_PreGain.Set(PreGain);
}

void CEffectsAppController::OnDelayBypassLeft(bool Bypass)
{
    m_DelayLeft.SetBypass(Bypass);
}

void CEffectsAppController::OnDelayWetDryLeft(float WetDry)
{
    m_DelayLeft.SetWet(WetDry);
}

void CEffectsAppController::OnDelayMilliSecondsLeft(float Delay)
{
    m_DelayTimeLeft.SetMilliSeconds(Delay);
    m_DelayLeft.SetDelay(m_DelayTimeLeft());
}

void CEffectsAppController::OnDelayFeedbackLeft(float Feedback)
{
    m_DelayLeft.SetFeedback(Feedback);
}

void CEffectsAppController::OnDelayBypassRight(bool Bypass)
{
    m_DelayRight.SetBypass(Bypass);
}

void CEffectsAppController::OnDelayWetDryRight(float WetDry)
{
    m_DelayRight.SetWet(WetDry);
}

void CEffectsAppController::OnDelayMilliSecondsRight(float Delay)
{
    m_DelayTimeRight.SetMilliSeconds(Delay);
    m_DelayRight.SetDelay(m_DelayTimeRight());
}

void CEffectsAppController::OnDelayFeedbackRight(float Feedback)
{
    m_DelayRight.SetFeedback(Feedback);
}

void CEffectsAppController::SetMasterVolume(float Volume)
{
    m_MasterVolume.Set(Volume);
}
