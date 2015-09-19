#include "IntCombinedOperatorFilter.h"
#include "IntConversions.h"

CIntCombinedOperatorFilter::CIntCombinedOperatorFilter(int SamplingFrequency)
    : m_Buffers({220.0f, 1.0f, 1.0f, 1.0f},{0.0f})
    , m_CombinedOperator(SamplingFrequency)
{
}

std::vector<std::string> CIntCombinedOperatorFilter::GetInputNames() const
{
    return { "Freq", "DetuneA", "DetuneB", "DetuneC" };
}

std::vector<std::string> CIntCombinedOperatorFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CIntCombinedOperatorFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CIntCombinedOperatorFilter::GetMidiOutputNames() const
{
    return {};
}

int CIntCombinedOperatorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                       const std::vector<void *> &DestinationBuffers,
                                       const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                       const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                       int NumFrames,
                                       std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const int FreqMultiplierScale = 10;//1024

    const float* FreqBuffer = m_Buffers.GetSourceBuffer(0);
    const float* DetuneABuffer = m_Buffers.GetSourceBuffer(1);
    const float* DetuneBBuffer = m_Buffers.GetSourceBuffer(2);
    const float* DetuneCBuffer = m_Buffers.GetSourceBuffer(3);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        m_CombinedOperator.SetFrequency((*FreqBuffer)*1000);
        m_CombinedOperator.SetFrequencyMultiplierA((*DetuneABuffer)*(1<<FreqMultiplierScale), FreqMultiplierScale);
        m_CombinedOperator.SetFrequencyMultiplierB((*DetuneBBuffer)*(1<<FreqMultiplierScale), FreqMultiplierScale);
        m_CombinedOperator.SetFrequencyMultiplierC((*DetuneCBuffer)*(1<<FreqMultiplierScale), FreqMultiplierScale);
        *OutBuffer = isl::IntBipolarToFloatBipolar<int, float, Scale>(m_CombinedOperator());
        ++FreqBuffer;
        ++DetuneABuffer;
        ++DetuneBBuffer;
        ++DetuneCBuffer;
        ++OutBuffer;
    }

    return 0;
}

void CIntCombinedOperatorFilter::SelectOperatorA(int Selected)
{
    m_CombinedOperator.SelectOperatorA(Selected);
}

void CIntCombinedOperatorFilter::SelectOperatorB(int Selected)
{
    m_CombinedOperator.SelectOperatorB(Selected);
}

void CIntCombinedOperatorFilter::SelectOperatorC(int Selected)
{
    m_CombinedOperator.SelectOperatorC(Selected);
}

void CIntCombinedOperatorFilter::SelectCombinor1(int Selected)
{
    m_CombinedOperator.SelectCombinor1(Selected);
}

void CIntCombinedOperatorFilter::SelectCombinor2(int Selected)
{
    m_CombinedOperator.SelectCombinor2(Selected);
}
