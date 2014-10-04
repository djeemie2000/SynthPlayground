#include "DelayLineFilter.h"

namespace
{
    const int MaxDelaySeconds = 5;
}

CDelayLineFilter::CDelayLineFilter(int SamplingFrequency)
 : m_DelayRange(SamplingFrequency)
 , m_DelayLine(MaxDelaySeconds*SamplingFrequency, 0.0f)//5sec max capacity
{
}

std::vector<std::string> CDelayLineFilter::GetInputNames() const
{
    return {"In", "Delay"};
}

std::vector<std::string> CDelayLineFilter::GetOutputNames() const
{
    return {"Delayed"};
}

std::vector<std::string> CDelayLineFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CDelayLineFilter::GetMidiOutputNames() const
{
    return {};
}

int CDelayLineFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                  const std::vector<void *> &DestinationBuffers,
                                  const std::vector<std::shared_ptr<IMidiRenderer> > /*MidiRenderers*/,
                                  const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                  int NumFrames,
                                  std::uint32_t /*TimeStamp*/)
{

        if(SourceBuffers[0] && SourceBuffers[1] && DestinationBuffers[0])
        {
            const float* Src = (const float*)SourceBuffers[0];
            const float* SrcEnd = Src + NumFrames;
            const float* Delay = (const float*)SourceBuffers[1];
            float* Dst = (float*)DestinationBuffers[0];
            while(Src<SrcEnd)
            {
                m_DelayLine.Write(*Src);
                *Dst = m_DelayLine.Read((*Delay)*m_DelayRange());
                ++Src;
                ++Delay;
                ++Dst;
            }
        }
        else if(SourceBuffers[0] && DestinationBuffers[0])
        {
            float* Dst = (float*)DestinationBuffers[0];
            const float* Src = (const float*)SourceBuffers[0];
            std::copy(Src, Src+NumFrames, Dst);
        }
        else if(DestinationBuffers[0])
        {
            //if only destination buffer=> all zero output
            float* Dst = (float*)DestinationBuffers[0];
            std::fill(Dst, Dst + NumFrames, 0.0f);
        }

        return 0;
}

void CDelayLineFilter::SetDelayRange(int DelayRangeMilliSeconds)
{
    m_DelayRange.SetMilliSeconds(DelayRangeMilliSeconds);
}

int CDelayLineFilter::GetMaxDelayMilliSeconds() const
{
    return MaxDelaySeconds*1000;
}

