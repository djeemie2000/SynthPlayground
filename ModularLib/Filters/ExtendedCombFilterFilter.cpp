#include "ExtendedCombFilterFilter.h"

CExtendedCombFilterFilter::CExtendedCombFilterFilter(int SamplingFrequency)
    : m_SamplingFrequency(SamplingFrequency)
    , m_CombFilter(SamplingFrequency)
    , m_Buffers({0.0f, 1.0f, 1.0f, -1.0f, 110.0f}, {0.0f})
{
}

std::vector<std::string> CExtendedCombFilterFilter::GetInputNames() const
{
    return {"In", "B0", "Bm", "Am", "Freq"};
}

std::vector<std::string> CExtendedCombFilterFilter::GetOutputNames() const
{
    return {"Out"};
}

std::vector<std::string> CExtendedCombFilterFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CExtendedCombFilterFilter::GetMidiOutputNames() const
{
    return {};
}

int CExtendedCombFilterFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                       const std::vector<void *> &DestinationBuffers,
                                       const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                       const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                       int NumFrames,
                                       std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const float* InBuffer = m_Buffers.GetSourceBuffer(0);
    const float* B0Buffer = m_Buffers.GetSourceBuffer(1);
    const float* BmBuffer = m_Buffers.GetSourceBuffer(2);
    const float* AmBuffer = m_Buffers.GetSourceBuffer(3);
    const float* FreqBuffer = m_Buffers.GetSourceBuffer(4);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        int Delay = m_SamplingFrequency/(*FreqBuffer);
        *OutBuffer = m_CombFilter(*InBuffer, *B0Buffer, *BmBuffer, *AmBuffer, Delay);
        ++InBuffer;
        ++B0Buffer;
        ++BmBuffer;
        ++AmBuffer;
        ++FreqBuffer;
        ++OutBuffer;
    }

    return 0;
}
