#include "IntSimpleOscillatorFilter.h"
#include "IntConversions.h"

CIntSimpleOscillatorFilter::CIntSimpleOscillatorFilter(int SamplingFrequency)
    : m_Oscillator(SamplingFrequency)
    , m_Buffers({220.0f},{0.0f})
{
}

std::vector<std::string> CIntSimpleOscillatorFilter::GetInputNames() const
{
    return {"Freq"};
}

std::vector<std::string> CIntSimpleOscillatorFilter::GetOutputNames() const
{
    return {"Out"};
}

std::vector<std::string> CIntSimpleOscillatorFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CIntSimpleOscillatorFilter::GetMidiOutputNames() const
{
    return {};
}

int CIntSimpleOscillatorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                       const std::vector<void *> &DestinationBuffers,
                                       const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                       const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                       int NumFrames,
                                       std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const float* FreqBuffer = m_Buffers.GetSourceBuffer(0);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        m_Oscillator.SetFrequency((*FreqBuffer)*1000);//Hz to milliHz
        *OutBuffer = isl::IntBipolarToFloatBipolar<int, float, Scale>(m_Oscillator());
        ++FreqBuffer;
        ++OutBuffer;
    }

    return 0;
}

void CIntSimpleOscillatorFilter::SelectWaveform(int Selection)
{
    m_Oscillator.SelectOperator(Selection);
}
