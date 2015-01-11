#include <algorithm>
#include "BipolarLimiterFilter.h"

CBipolarLimiterFilter::CBipolarLimiterFilter()
 : m_Limiter()
{
}

std::vector<std::string> CBipolarLimiterFilter::GetInputNames() const
{
    return { "In" };
}

std::vector<std::string> CBipolarLimiterFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CBipolarLimiterFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CBipolarLimiterFilter::GetMidiOutputNames() const
{
    return {};
}

int CBipolarLimiterFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                      const std::vector<void *> &DestinationBuffers,
                                      const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                      const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                      int NumFrames,
                                      std::uint32_t /*TimeStLimiter*/)
{
    const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(OutBuffer)
    {
        if(InBuffer)
        {
            float* OutBufferEnd = OutBuffer + NumFrames;
            while(OutBuffer<OutBufferEnd)
            {
                *OutBuffer = m_Limiter(*InBuffer);
                ++OutBuffer;
                ++InBuffer;
            }
        }
        else
        { // no input => output all zeros
            std::fill(OutBuffer, OutBuffer + NumFrames, 0.0f);
        }
    }

    return 0;
}
