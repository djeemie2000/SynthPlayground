#include "StereoDelayFilter.h"

CStereoDelayFilter::CStereoDelayFilter(int SamplingFrequency)
 : m_DelayTime(2, CConstNumSamplesGenerator<float>(static_cast<float>(SamplingFrequency)))
 , m_Delay(2, CFeedbackDelay<float>(5*SamplingFrequency, 0.0f))
{
}

std::vector<std::string> CStereoDelayFilter::GetInputNames() const
{
    return {"InLeft", "InRight"};
}

std::vector<std::string> CStereoDelayFilter::GetOutputNames() const
{
    return {"OutLeft", "OutRight"};
}

std::vector<std::string> CStereoDelayFilter::GetMidiInputNames() const
{
    return {};
}

int CStereoDelayFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                  const std::vector<void *> &DestinationBuffers,
                                  const std::vector<std::shared_ptr<IMidiRenderer> > /*MidiRenderers*/,
                                  int NumFrames,
                                  std::uint32_t /*TimeStamp*/)
{
    for(int idx = 0; idx<2; ++idx)
    {
        if(SourceBuffers[idx] && DestinationBuffers[idx])
        {
            const float* pSrcL = (const float*)SourceBuffers[idx];
            const float* pSrcEndL = pSrcL + NumFrames;
            float* pDstL = (float*)DestinationBuffers[idx];
            while(pSrcL<pSrcEndL)
            {
                *pDstL =  m_Delay[idx](*pSrcL);
                ++pSrcL;
                ++pDstL;
            }
        }
        else if(DestinationBuffers[idx])
        {
            //if only destination buffer=> all zero output
            float* Dst = (float*)DestinationBuffers[idx];
            std::fill(Dst, Dst + NumFrames, 0.0f);
        }
    }

    return 0;
}

void CStereoDelayFilter::OnDelayBypass(int Index, bool Bypass)
{
    m_Delay[Index].SetBypass(Bypass);
}

void CStereoDelayFilter::OnDelayWetDry(int Index, float WetDry)
{
    m_Delay[Index].SetWet(WetDry);
}

void CStereoDelayFilter::OnDelayMilliSeconds(int Index, float Delay)
{
    m_DelayTime[Index].SetMilliSeconds(Delay);
    m_Delay[Index].SetDelay(m_DelayTime[Index]());
}

void CStereoDelayFilter::OnDelayFeedback(int Index, float Feedback)
{
    m_Delay[Index].SetFeedback(Feedback);
}
