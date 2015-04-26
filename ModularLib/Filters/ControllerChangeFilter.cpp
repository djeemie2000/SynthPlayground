#include <algorithm>
#include "ControllerChangeFilter.h"
#include "ControllerChange.h"

CControllerChangeFilter::CControllerChangeFilter(int SamplingFrequency)
    : m_DefaultRateValue(1.0f/SamplingFrequency)
    , m_ControllerChange()
    , m_DefaultRate()
    , m_DefaultIncr()
    , m_DefaultDecr()
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
        if(static_cast<int>(m_DefaultDecr.size())<NumFrames)
        {
            const float DefaultDecr = 0.0f;
            m_DefaultDecr.assign(NumFrames, DefaultDecr);
        }
        if(static_cast<int>(m_DefaultIncr.size())<NumFrames)
        {
            const float DefaultIncr = 0.0f;
            m_DefaultIncr.assign(NumFrames, DefaultIncr);
        }
        if(static_cast<int>(m_DefaultRate.size())<NumFrames)
        {
            // rate = 1/samplingfreq => 1 second needed to go from min to max
            m_DefaultRate.assign(NumFrames, 0.5);
        }

        const float* IncrBuffer = SourceBuffers[0] ? static_cast<const float*>(SourceBuffers[0]) : m_DefaultIncr.data();
        const float* RateBuffer = SourceBuffers[1] ? static_cast<const float*>(SourceBuffers[1]) : m_DefaultRate.data();
        const float* DecrBuffer = SourceBuffers[2] ? static_cast<const float*>(SourceBuffers[2]) : m_DefaultDecr.data();

        const float* IncrBufferEnd = IncrBuffer + NumFrames;
        while(IncrBuffer<IncrBufferEnd)
        {
            *OutBuffer = m_ControllerChange(*IncrBuffer, *DecrBuffer, *RateBuffer*m_DefaultRateValue);
            ++IncrBuffer;
            ++RateBuffer;
            ++DecrBuffer;
            ++OutBuffer;
        }

    }

    return 0;
}
