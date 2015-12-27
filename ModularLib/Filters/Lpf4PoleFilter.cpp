#include <algorithm>
#include "Lpf4PoleFilter.h"

CLpf4PoleFilter::CLpf4PoleFilter()
 : m_LPFilter()
{
}

std::vector<std::string> CLpf4PoleFilter::GetInputNames() const
{
    return { "In", "CutOff" };
}

std::vector<std::string> CLpf4PoleFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CLpf4PoleFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CLpf4PoleFilter::GetMidiOutputNames() const
{
    return {};
}

int CLpf4PoleFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(OutBuffer)
    {
        const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
        const float* CutoffBuffer = static_cast<const float*>(SourceBuffers[1]);
        if(InBuffer && CutoffBuffer)
        {
            const float* InBufferEnd = InBuffer+NumFrames;
            while(InBuffer<InBufferEnd)
            {
                *OutBuffer = m_LPFilter(*InBuffer, *CutoffBuffer);
                ++InBuffer;
                ++CutoffBuffer;
                ++OutBuffer;
            }
        }
        else
        {
            std::fill(OutBuffer, OutBuffer+NumFrames, 0.0f);
        }
    }

    return 0;
}
