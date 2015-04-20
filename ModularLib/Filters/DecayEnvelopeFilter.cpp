#include <algorithm>
#include "DecayEnvelopeFilter.h"

CDecayEnvelopeFilter::CDecayEnvelopeFilter()
 : m_Envelope()
{
}

std::vector<std::string> CDecayEnvelopeFilter::GetInputNames() const
{
    return { "Trigger", "Decay" };
}

std::vector<std::string> CDecayEnvelopeFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CDecayEnvelopeFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CDecayEnvelopeFilter::GetMidiOutputNames() const
{
    return {};
}

int CDecayEnvelopeFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* TriggerBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* DecayBuffer = static_cast<const float*>(SourceBuffers[1]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(TriggerBuffer && OutBuffer && DecayBuffer)
    {
        const float* TriggerBufferEnd = TriggerBuffer+NumFrames;
        while(TriggerBuffer<TriggerBufferEnd)
        {
            *OutBuffer = m_Envelope(*TriggerBuffer, *DecayBuffer);
            ++TriggerBuffer;
            ++OutBuffer;
            ++DecayBuffer;
        }
    }

    return 0;
}
