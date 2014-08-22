#include <algorithm>
#include "AmpFilter.h"
#include "Amp.h"

CAmpFilter::CAmpFilter()
 : m_Amp()
{
}

std::vector<std::string> CAmpFilter::GetInputNames() const
{
    return { "In", "Ampl" };
}

std::vector<std::string> CAmpFilter::GetOutputNames() const
{
    return { "Out" };
}

int CAmpFilter::OnProcess(const std::vector<void *> &SourceBuffers, const std::vector<void *> &DestinationBuffers, int NumFrames, std::uint32_t /*TimeStamp*/)
{
    const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* AmplBuffer = static_cast<const float*>(SourceBuffers[1]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(InBuffer && OutBuffer && AmplBuffer)
    {
        std::transform(InBuffer, InBuffer+NumFrames, AmplBuffer, OutBuffer, m_Amp);
    }

    return 0;
}
