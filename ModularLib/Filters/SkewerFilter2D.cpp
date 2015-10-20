#include <algorithm>
#include "SkewerFilter2D.h"
#include "PhaseSkewer2D.h"

CPhaseSkewer2DFilter::CPhaseSkewer2DFilter()
    : m_Buffers({0.0f, 0.0f, 0.0f},{0.0f})
    , m_Skewer()
{
}

std::vector<std::string> CPhaseSkewer2DFilter::GetInputNames() const
{
    return { "Phase", "SkewX", "SkewY" };
}

std::vector<std::string> CPhaseSkewer2DFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CPhaseSkewer2DFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CPhaseSkewer2DFilter::GetMidiOutputNames() const
{
    return {};
}

int CPhaseSkewer2DFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const float* PhaseBuffer = m_Buffers.GetSourceBuffer(0);
    const float* SkewXBuffer = m_Buffers.GetSourceBuffer(1);
    const float* SkewYBuffer = m_Buffers.GetSourceBuffer(2);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer +  NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        *OutBuffer = m_Skewer(*PhaseBuffer, *SkewXBuffer, *SkewYBuffer);

        ++OutBuffer;
        ++PhaseBuffer;
        ++SkewXBuffer;
        ++SkewYBuffer;
    }

    return 0;
}
