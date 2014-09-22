#include <algorithm>
#include "SampleAndHoldFilter.h"

CSampleAndHoldFilter::CSampleAndHoldFilter()
 : m_SampleAndHold()
{
}

std::vector<std::string> CSampleAndHoldFilter::GetInputNames() const
{
    return { "In", "Trigger" };
}

std::vector<std::string> CSampleAndHoldFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CSampleAndHoldFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CSampleAndHoldFilter::GetMidiOutputNames() const
{
    return {};
}

int CSampleAndHoldFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    if(float* OutBuffer = static_cast<float*>(DestinationBuffers[0]))
    {
        const float* InBuffer = static_cast<float*>(SourceBuffers[0]);
        const float* TriggerBuffer = static_cast<float*>(SourceBuffers[1]);
        if(InBuffer && TriggerBuffer)
        {
            const float* OutBufferEnd = OutBuffer + NumFrames;
            while(OutBuffer<OutBufferEnd)
            {
                *OutBuffer = m_SampleAndHold(*InBuffer, 0.99<*TriggerBuffer);
                ++InBuffer;
                ++TriggerBuffer;
                ++OutBuffer;
            }
        }
        else if(InBuffer)
        {
            std::copy(InBuffer, InBuffer + NumFrames, OutBuffer);
        }
    }

    return 0;
}
