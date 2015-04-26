#include <algorithm>
#include "ControllerChangeFilter.h"
#include "ControllerChange.h"

CControllerChangeFilter::CControllerChangeFilter()
 : m_ControllerChange()
{
}

std::vector<std::string> CControllerChangeFilter::GetInputNames() const
{
    return { "Incr", "Rate", "Decr" };
}

std::vector<std::string> CControllerChangeFilter::GetOutputNames() const
{
    return { "CV" };
}

std::vector<std::string> CControllerChangeFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CControllerChangeFilter::GetMidiOutputNames() const
{
    return {};
}

int CControllerChangeFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(OutBuffer)
    {
        const float* IncrBuffer = static_cast<const float*>(SourceBuffers[0]);
        const float* RateBuffer = static_cast<const float*>(SourceBuffers[1]);
        const float* DecrBuffer = static_cast<const float*>(SourceBuffers[2]);
        if(IncrBuffer && RateBuffer && DecrBuffer)
        {
            const float* IncrBufferEnd = IncrBuffer + NumFrames;
            while(IncrBuffer<IncrBufferEnd)
            {
                *OutBuffer = m_ControllerChange(*IncrBuffer, *DecrBuffer, *RateBuffer);
                ++IncrBuffer;
                ++RateBuffer;
                ++DecrBuffer;
                ++OutBuffer;
            }
        }
        else if(IncrBuffer && RateBuffer)
        {
            const float* IncrBufferEnd = IncrBuffer + NumFrames;
            while(IncrBuffer<IncrBufferEnd)
            {
                *OutBuffer = m_ControllerChange(*IncrBuffer, 0.0f, *RateBuffer);
                ++IncrBuffer;
                ++RateBuffer;
                ++OutBuffer;
            }
        }
        else if(DecrBuffer && RateBuffer)
        {
            const float* DecrBufferEnd = DecrBuffer + NumFrames;
            while(DecrBuffer<DecrBufferEnd)
            {
                *OutBuffer = m_ControllerChange(0.0f, *DecrBuffer, *RateBuffer);
                ++DecrBuffer;
                ++RateBuffer;
                ++OutBuffer;
            }
        }
        else // only IncrBuffer or only DecrBuffer or only RateBuffer => constant value
        {
            const float* OutBufferEnd = OutBuffer + NumFrames;
            while(OutBuffer<OutBufferEnd)
            {
                *OutBuffer = m_ControllerChange(0.0f, 0.0f, 0.0f);
                ++OutBuffer;
            }
        }
        // TODO use default rate when rate is not connected?
        // rate = n/samplingfreq => 1/n second needed to go from min to max
        // TODO use default buffers for incr, decr, rate to simplify code (use default buffer when no source buffer)
    }

    return 0;
}
