#include <algorithm>
#include "SlewLimiterFilter.h"
#include "SlewLimiter.h"

CSlewLimiterFilter::CSlewLimiterFilter()
 : m_SlewLimiter(0.0f)
{
}

std::vector<std::string> CSlewLimiterFilter::GetInputNames() const
{
    return { "In", "Slew+", "Slew-" };
}

std::vector<std::string> CSlewLimiterFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CSlewLimiterFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CSlewLimiterFilter::GetMidiOutputNames() const
{
    return {};
}

int CSlewLimiterFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStSlewLimiter*/)
{
    if(float* OutBuffer = static_cast<float*>(DestinationBuffers[0]))
    {
        const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
        const float* SlewNegBuffer = static_cast<const float*>(SourceBuffers[1]);
        const float* SlewPosBuffer = static_cast<const float*>(SourceBuffers[2]);
        if(InBuffer)
        {
            if(SlewPosBuffer && SlewNegBuffer)
            {
                const float* InBufferEnd = InBuffer + NumFrames;
                while(InBuffer<InBufferEnd)
                {
                    *OutBuffer = m_SlewLimiter(*InBuffer, *SlewPosBuffer, *SlewNegBuffer);
                    ++OutBuffer;
                    ++InBuffer;
                    ++SlewPosBuffer;
                    ++SlewNegBuffer;
                }
            }
            else if(SlewPosBuffer)
            { // no slew neg buffer => use zero for neg
                const float* InBufferEnd = InBuffer + NumFrames;
                while(InBuffer<InBufferEnd)
                {
                    *OutBuffer = m_SlewLimiter(*InBuffer, *SlewPosBuffer, 0.0f);
                    ++OutBuffer;
                    ++InBuffer;
                    ++SlewPosBuffer;
                }
            }
            else if(SlewNegBuffer)
            {
                // no slew pos => use zero for slew pos
                const float* InBufferEnd = InBuffer + NumFrames;
                while(InBuffer<InBufferEnd)
                {
                    *OutBuffer = m_SlewLimiter(*InBuffer, 0.0f, *SlewNegBuffer);
                    ++OutBuffer;
                    ++InBuffer;
                    ++SlewNegBuffer;
                }
            }
            else
            { // no pos or neg slew => both zero => out all zeros
                std::fill(OutBuffer, OutBuffer + NumFrames, 0.0f);
            }
        }
        else
        {
            std::fill(OutBuffer, OutBuffer + NumFrames, 0.0f);
        }
    }

    return 0;
}
