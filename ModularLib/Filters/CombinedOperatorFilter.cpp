#include "CombinedOperatorFilter.h"

CCombinedOperatorFilter::CCombinedOperatorFilter(int SamplingFrequency)
    : m_Buffers({220.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},{0.0f})
    , m_CombinedOperator(SamplingFrequency)
{
}

std::vector<std::string> CCombinedOperatorFilter::GetInputNames() const
{
    return { "Freq", "DetuneA", "ShiftA", "DetuneB", "ShiftB", "DetuneC", "ShiftC" };
}

std::vector<std::string> CCombinedOperatorFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CCombinedOperatorFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CCombinedOperatorFilter::GetMidiOutputNames() const
{
    return {};
}

int CCombinedOperatorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                       const std::vector<void *> &DestinationBuffers,
                                       const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                       const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                       int NumFrames,
                                       std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const float* FreqBuffer = m_Buffers.GetSourceBuffer(0);
    const float* DetuneABuffer = m_Buffers.GetSourceBuffer(1);
    const float* ShiftABuffer = m_Buffers.GetSourceBuffer(2);
    const float* DetuneBBuffer = m_Buffers.GetSourceBuffer(3);
    const float* ShiftBBuffer = m_Buffers.GetSourceBuffer(4);
    const float* DetuneCBuffer = m_Buffers.GetSourceBuffer(5);
    const float* ShiftCBuffer = m_Buffers.GetSourceBuffer(6);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        *OutBuffer = m_CombinedOperator(*FreqBuffer,
                                        *DetuneABuffer, *ShiftABuffer,
                                        *DetuneBBuffer, *ShiftBBuffer,
                                        *DetuneCBuffer, *ShiftCBuffer);
        ++FreqBuffer;
        ++DetuneABuffer;
        ++ShiftABuffer;
        ++DetuneBBuffer;
        ++ShiftBBuffer;
        ++DetuneCBuffer;
        ++ShiftCBuffer;
        ++OutBuffer;
    }

    return 0;
}

void CCombinedOperatorFilter::SelectOperatorA(int Selected)
{
    m_CombinedOperator.SelectOperatorA(Selected);
}

void CCombinedOperatorFilter::SelectOperatorB(int Selected)
{
    m_CombinedOperator.SelectOperatorB(Selected);
}

void CCombinedOperatorFilter::SelectOperatorC(int Selected)
{
    m_CombinedOperator.SelectOperatorC(Selected);
}

void CCombinedOperatorFilter::SelectCombinor(int Selected)
{
    m_CombinedOperator.SelectCombinor(Selected);
}

void CCombinedOperatorFilter::SelectCombinor2(int Selected)
{
    m_CombinedOperator.SelectCombinor2(Selected);
}
