#include "DelayVerbFilter.h"

namespace
{
const int MaxDelaySeconds = 4;
}

CDelayVerbFilter::CDelayVerbFilter(int SamplingFrequency)
    : m_DelayRange(MaxDelaySeconds*SamplingFrequency/20)
    , m_DelayVerb(MaxDelaySeconds*SamplingFrequency)//1 sec max capacity
    , m_Buffers({0.0f, 0.0f, 0.5f, 1.0f}, {0.0f})
{
}

std::vector<std::string> CDelayVerbFilter::GetInputNames() const
{
    return {"In", "Feedback", "Delay", "Damp"};
}

std::vector<std::string> CDelayVerbFilter::GetOutputNames() const
{
    return {"Out"};
}

std::vector<std::string> CDelayVerbFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CDelayVerbFilter::GetMidiOutputNames() const
{
    return {};
}

int CDelayVerbFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                const std::vector<void *> &DestinationBuffers,
                                const std::vector<std::shared_ptr<IMidiRenderer> > /*MidiRenderers*/,
                                const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                int NumFrames,
                                std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const float* InBuffer = m_Buffers.GetSourceBuffer(0);
    const float* FeedbackBuffer = m_Buffers.GetSourceBuffer(1);
    const float* DelayBuffer = m_Buffers.GetSourceBuffer(2);
    const float* DampBuffer = m_Buffers.GetSourceBuffer(3);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        *OutBuffer = m_DelayVerb(*InBuffer, *FeedbackBuffer,(*DelayBuffer)*m_DelayRange, *DampBuffer);
        ++InBuffer;
        ++FeedbackBuffer;
        ++DelayBuffer;
        ++DampBuffer;
        ++OutBuffer;
    }

    return 0;
}

