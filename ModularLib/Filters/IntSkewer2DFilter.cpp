#include <algorithm>
#include "IntSkewer2DFilter.h"
#include "IntSkewer2D.h"
#include "IntOperators.h"
#include "IntConversions.h"

CIntSkewer2DFilter::CIntSkewer2DFilter()
    : m_Buffers({0.0f, 0.0f, 0.0f},{0.0f})
    , m_Skewer(isl::IntMinSigned<Scale>(), isl::IntMinSigned<Scale>(), isl::IntMaxSigned<Scale>(), isl::IntMaxSigned<Scale>())
{
}

std::vector<std::string> CIntSkewer2DFilter::GetInputNames() const
{
    return { "Phase", "SkewX", "SkewY" };
}

std::vector<std::string> CIntSkewer2DFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CIntSkewer2DFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CIntSkewer2DFilter::GetMidiOutputNames() const
{
    return {};
}

int CIntSkewer2DFilter::OnProcess(const std::vector<void *> &SourceBuffers,
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
        m_Skewer.SetSkew(isl::FloatBipolarToIntBipolar<int, float, Scale>(*SkewXBuffer),
                         isl::FloatBipolarToIntBipolar<int, float, Scale>(*SkewYBuffer));
        *OutBuffer = isl::IntBipolarToFloatBipolar<int, float, Scale>( m_Skewer(isl::FloatBipolarToIntBipolar<int, float, Scale>(*PhaseBuffer)) );

        ++OutBuffer;
        ++PhaseBuffer;
        ++SkewXBuffer;
        ++SkewYBuffer;
    }

    return 0;
}
