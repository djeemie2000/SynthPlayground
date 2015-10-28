#include "IntCombFilterFilter.h"
#include "IntConversions.h"
#include "IntUtilities.h"

CIntCombFilterFilter::CIntCombFilterFilter(int SamplingFrequency)
    : m_SamplingFrequency(SamplingFrequency)
    , m_CombFilter()
    , m_Buffers({0.0f, 1.0f, 110.0f, 0.0f}, {0.0f})
{
    m_CombFilter.SetWetDry(1<<1, 1);
}

std::vector<std::string> CIntCombFilterFilter::GetInputNames() const
{
    return {"In", "Ampl", "Freq", "Feedback"};
}

std::vector<std::string> CIntCombFilterFilter::GetOutputNames() const
{
    return {"Out"};
}

std::vector<std::string> CIntCombFilterFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CIntCombFilterFilter::GetMidiOutputNames() const
{
    return {};
}

int CIntCombFilterFilter::OnProcess(const std::vector<void *> &SourceBuffers,
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
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        m_CombFilter.SetDelay(isl::CalcPeriodSamples<int>(m_SamplingFrequency, (*FreqBuffer)*1000));
        m_CombFilter.SetFeedback((*FeedbackBuffer)*(1<<8), 8);
        int In = isl::FloatBipolarToIntBipolar<int, float, Scale>((*InBuffer)*(*AmplBuffer));
        *OutBuffer = isl::IntBipolarToFloatBipolar<int, float, Scale>(m_CombFilter(In));
        ++InBuffer;
        ++AmplBuffer;
        ++FreqBuffer;
        ++OutBuffer;
    }

    return 0;
}
