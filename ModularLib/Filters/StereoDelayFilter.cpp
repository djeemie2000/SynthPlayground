#include "StereoDelayFilter.h"

CStereoDelayFilter::CStereoDelayFilter(int SamplingFrequency)
    : m_DelayTime(Size, CConstNumSamplesGenerator<float>(static_cast<float>(SamplingFrequency)))
    , m_Delay(Size, CFeedbackDelay<float>(5*SamplingFrequency, 0.0f))
    , m_Buffers({0.0f, 0.0f}, {0.0f, 0.0f})
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

std::vector<std::string> CStereoDelayFilter::GetMidiOutputNames() const
{
    return {};
}

int CStereoDelayFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                  const std::vector<void *> &DestinationBuffers,
                                  const std::vector<std::shared_ptr<IMidiRenderer> > /*MidiRenderers*/,
                                  const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                  int NumFrames,
                                  std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);
    for(int idx = 0; idx<Size; ++idx)
    {
        const float* pSrc = m_Buffers.GetSourceBuffer(idx); //(const float*)SourceBuffers[idx];
        const float* pSrcEnd = pSrc + NumFrames;
        float* pDst = m_Buffers.GetDestinationBuffer(idx);//(float*)DestinationBuffers[idx];
        while(pSrc<pSrcEnd)
        {
            *pDst =  m_Delay[idx](*pSrc);
            ++pSrc;
            ++pDst;
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
