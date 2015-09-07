#include <algorithm>
#include "WaveShaperA116Filter.h"
#include "WaveShaperA116.h"

CWaveShaperA116Filter::CWaveShaperA116Filter()
    : m_Buffers({0.0f, -1.0f, 1.0f, 0.0f}, {0.0f})
{
}

std::vector<std::string> CWaveShaperA116Filter::GetInputNames() const
{
    return { "In", "LowTh", "HighTh", "Symmetry" };
}

std::vector<std::string> CWaveShaperA116Filter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CWaveShaperA116Filter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CWaveShaperA116Filter::GetMidiOutputNames() const
{
    return {};
}

int CWaveShaperA116Filter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const float* InBuffer = m_Buffers.GetSourceBuffer(0);
    const float* LowThBuffer = m_Buffers.GetSourceBuffer(1);
    const float* HighThBuffer = m_Buffers.GetSourceBuffer(2);
    const float* SymmetryBuffer = m_Buffers.GetSourceBuffer(3);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    CWaveShaperA116<float> WaveShaperA116;

    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        *OutBuffer = WaveShaperA116(*InBuffer, *LowThBuffer, *HighThBuffer, *SymmetryBuffer);
        ++InBuffer;
        ++LowThBuffer;
        ++HighThBuffer;
        ++SymmetryBuffer;
        ++OutBuffer;
    }
    return 0;
}
