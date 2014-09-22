#include <algorithm>
#include "SkewerFilter.h"
#include "PhaseSkewer.h"

CPhaseSkewerFilter::CPhaseSkewerFilter()
 : m_Skewer()
{
}

std::vector<std::string> CPhaseSkewerFilter::GetInputNames() const
{
    return { "Phase", "Skew" };
}

std::vector<std::string> CPhaseSkewerFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CPhaseSkewerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CPhaseSkewerFilter::GetMidiOutputNames() const
{
    return {};
}

int CPhaseSkewerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
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
