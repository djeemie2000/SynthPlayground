#include "CombFilterFilter.h"

CCombFilterFilter::CCombFilterFilter(int SamplingFrequency)
    : m_CombFilter(SamplingFrequency)
    , m_Buffers({0.0f, 1.0f, 110.0f, 0.0f, 1.0f}, {0.0f})
{
}

std::vector<std::string> CCombFilterFilter::GetInputNames() const
{
    return {"In", "Ampl", "Freq", "Feedback", "CutOff"};
}

std::vector<std::string> CCombFilterFilter::GetOutputNames() const
{
    return {"Out"};
}

std::vector<std::string> CCombFilterFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CCombFilterFilter::GetMidiOutputNames() const
{
    return {};
}

int CCombFilterFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                       const std::vector<void *> &DestinationBuffers,
                                       const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                       const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                       int NumFrames,
                                       std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const float* InBuffer = m_Buffers.GetSourceBuffer(0);
    const float* AmplBuffer = m_Buffers.GetSourceBuffer(1);
    const float* FreqBuffer = m_Buffers.GetSourceBuffer(2);
    const float* FeedbackBuffer = m_Buffers.GetSourceBuffer(3);
    const float* CutOffBuffer = m_Buffers.GetSourceBuffer(4);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        *OutBuffer = m_CombFilter((*InBuffer)*(*AmplBuffer), *FeedbackBuffer, *FreqBuffer, *CutOffBuffer);
        ++InBuffer;
        ++AmplBuffer;
        ++FreqBuffer;
        ++FeedbackBuffer;
        ++CutOffBuffer;
        ++OutBuffer;
    }

    return 0;
}
