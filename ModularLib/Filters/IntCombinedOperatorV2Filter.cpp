#include "IntCombinedOperatorV2Filter.h"
#include "IntConversions.h"

CIntCombinedOperatorV2Filter::CIntCombinedOperatorV2Filter(int SamplingFrequency)
    : m_Buffers({220.0f, 0.0f},{0.0f})
    , m_CombinedOperator()
{
    m_CombinedOperator.SetSamplingFrequency(SamplingFrequency);
}

std::vector<std::string> CIntCombinedOperatorV2Filter::GetInputNames() const
{
    return { "Freq", "Strength" };
}

std::vector<std::string> CIntCombinedOperatorV2Filter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CIntCombinedOperatorV2Filter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CIntCombinedOperatorV2Filter::GetMidiOutputNames() const
{
    return {};
}

int CIntCombinedOperatorV2Filter::OnProcess(const std::vector<void *> &SourceBuffers,
                                       const std::vector<void *> &DestinationBuffers,
                                       const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                       const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                       int NumFrames,
                                       std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const float* FreqBuffer = m_Buffers.GetSourceBuffer(0);
    const float* StrengthBuffer = m_Buffers.GetSourceBuffer(1);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        m_CombinedOperator.SetFrequency((*FreqBuffer)*(1<<FrequencyScale));
        m_CombinedOperator.SetCombinor1Strength((*StrengthBuffer)*(1<<StrengthScale));
        *OutBuffer = isl::IntBipolarToFloatBipolar<int, float, OperatorScale>(m_CombinedOperator());
        ++FreqBuffer;
        ++StrengthBuffer;
        ++OutBuffer;
    }

    return 0;
}

void CIntCombinedOperatorV2Filter::SelectOperatorA(int Selected)
{
    m_CombinedOperator.SelectOperatorA(Selected);
}

void CIntCombinedOperatorV2Filter::SelectOperatorB(int Selected)
{
    m_CombinedOperator.SelectOperatorB(Selected);
}

void CIntCombinedOperatorV2Filter::SelectCombinor1(int Selected)
{
    m_CombinedOperator.SelectCombinor1(Selected);
}

void CIntCombinedOperatorV2Filter::SetFrequencyMultiplierA(int Multiplier)
{
    m_CombinedOperator.SetFrequencyMultiplierA(Multiplier);
}

void CIntCombinedOperatorV2Filter::SetFrequencyMultiplierB(int Multiplier)
{
    m_CombinedOperator.SetFrequencyMultiplierB(Multiplier);
}
