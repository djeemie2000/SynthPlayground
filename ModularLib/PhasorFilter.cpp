#include <algorithm>
#include "PhasorFilter.h"

CPhasorFilter::CPhasorFilter(int SamplingFrequency)
    : m_PhaseStep(SamplingFrequency)
{
}

std::vector<std::string> CPhasorFilter::GetInputNames() const
{
    return {"Freq"};
}

std::vector<std::string> CPhasorFilter::GetOutputNames() const
{
    return {"Phase"};
}

int CPhasorFilter::OnProcess(const std::vector<void *> &SourceBuffers, const std::vector<void *> &DestinationBuffers, int NumFrames, std::uint32_t /*TimeStamp*/)
{
    const float* FreqBuffer = static_cast<const float*>(SourceBuffers[0]);
    float* PhaseBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(FreqBuffer && PhaseBuffer)
    {
        std::transform(FreqBuffer, FreqBuffer+NumFrames, PhaseBuffer, m_PhaseStep);
    }

    return 0;
}
