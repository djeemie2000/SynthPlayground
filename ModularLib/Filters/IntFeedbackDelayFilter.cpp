#include "IntFeedbackDelayFilter.h"
#include "IntConversions.h"

CIntFeedbackDelayFilter::CIntFeedbackDelayFilter(int /*SamplingFrequency*/)
    : m_FeedbackDelay()
    , m_Buffers({0.0f, 0.0f, 0.0f, 0.0f}, {0.0f})
{
}

std::vector<std::string> CIntFeedbackDelayFilter::GetInputNames() const
{
    return {"In", "DryWet", "Delay", "Feedback"};
}

std::vector<std::string> CIntFeedbackDelayFilter::GetOutputNames() const
{
    return {"Out"};
}

std::vector<std::string> CIntFeedbackDelayFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CIntFeedbackDelayFilter::GetMidiOutputNames() const
{
    return {};
}

int CIntFeedbackDelayFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                       const std::vector<void *> &DestinationBuffers,
                                       const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                       const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                       int NumFrames,
                                       std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const float* InBuffer = m_Buffers.GetSourceBuffer(0);
    const float* DryWetBuffer = m_Buffers.GetSourceBuffer(1);
    const float* DelayBuffer = m_Buffers.GetSourceBuffer(2);
    const float* FeedbackBuffer = m_Buffers.GetSourceBuffer(3);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        m_FeedbackDelay.SetWetDry((*DryWetBuffer)*(1<<8), 8);
        m_FeedbackDelay.SetDelay((*DelayBuffer)*Capacity);
        m_FeedbackDelay.SetFeedback((*FeedbackBuffer)*(1<<8), 8);
        int In = isl::FloatBipolarToIntBipolar<int, float, Scale>(*InBuffer);
        *OutBuffer = isl::IntBipolarToFloatBipolar<int, float, Scale>(m_FeedbackDelay(In));
        ++InBuffer;
        ++DryWetBuffer;
        ++DelayBuffer;
        ++OutBuffer;
    }

    return 0;
}
