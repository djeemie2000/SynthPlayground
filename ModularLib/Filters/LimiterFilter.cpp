#include <algorithm>
#include "LimiterFilter.h"
#include "Limiter.h"

CLimiterFilter::CLimiterFilter()
 : m_Limiter()
{
}

std::vector<std::string> CLimiterFilter::GetInputNames() const
{
    return { "In", "Min", "Max" };
}

std::vector<std::string> CLimiterFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CLimiterFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CLimiterFilter::GetMidiOutputNames() const
{
    return {};
}

int CLimiterFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStLimiter*/)
{
    const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* MinBuffer = static_cast<const float*>(SourceBuffers[1]);
    const float* MaxBuffer = static_cast<const float*>(SourceBuffers[2]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(OutBuffer)
    {
        if(InBuffer)
        {
            if(MinBuffer && MaxBuffer)
            {
                float* OutBufferEnd = OutBuffer + NumFrames;
                while(OutBuffer<OutBufferEnd)
                {
                    *OutBuffer = m_Limiter(*InBuffer, *MinBuffer, *MaxBuffer);
                    ++OutBuffer;
                    ++InBuffer;
                    ++MinBuffer;
                    ++MaxBuffer;
                }
            }
            else if(MinBuffer)
            { // use max = 0
                float* OutBufferEnd = OutBuffer + NumFrames;
                while(OutBuffer<OutBufferEnd)
                {
                    *OutBuffer = m_Limiter(*InBuffer, *MinBuffer, 0.0f);
                    ++OutBuffer;
                    ++InBuffer;
                    ++MinBuffer;
                }
            }
            else if(MaxBuffer)
            { // use min = 0
                float* OutBufferEnd = OutBuffer + NumFrames;
                while(OutBuffer<OutBufferEnd)
                {
                    *OutBuffer = m_Limiter(*InBuffer, 0.0f, *MaxBuffer);
                    ++OutBuffer;
                    ++InBuffer;
                    ++MaxBuffer;
                }
            }
            else
            {
                std::fill(OutBuffer, OutBuffer + NumFrames, 0.0f);
            }
        }
        else
        { // no input => output all zeros
            std::fill(OutBuffer, OutBuffer + NumFrames, 0.0f);
        }
    }

    return 0;
}
