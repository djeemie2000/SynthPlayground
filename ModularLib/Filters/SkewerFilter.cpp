#include <algorithm>
#include "SkewerFilter.h"
#include "PhaseSkewer.h"

CSkewerFilter::CSkewerFilter()
 : m_Skewer()
{
}

std::vector<std::string> CSkewerFilter::GetInputNames() const
{
    return { "Phase", "Skew" };
}

std::vector<std::string> CSkewerFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CSkewerFilter::GetMidiInputNames() const
{
    return {};
}

int CSkewerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* PhaseBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* SkewBuffer = static_cast<const float*>(SourceBuffers[1]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(PhaseBuffer && OutBuffer && SkewBuffer)
    {
        std::transform(PhaseBuffer, PhaseBuffer+NumFrames, SkewBuffer, OutBuffer, m_Skewer);
    }

    return 0;
}
