#include <algorithm>
#include "EnvelopeFollowerFilter.h"

CEnvelopeFollowerFilter::CEnvelopeFollowerFilter(int SamplingFrequency)
 : m_EnvelopeFollower(static_cast<float>(SamplingFrequency))
{
}

std::vector<std::string> CEnvelopeFollowerFilter::GetInputNames() const
{
    return { "In" };
}

std::vector<std::string> CEnvelopeFollowerFilter::GetOutputNames() const
{
    return { "Env" };
}

std::vector<std::string> CEnvelopeFollowerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CEnvelopeFollowerFilter::GetMidiOutputNames() const
{
    return {};
}

int CEnvelopeFollowerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(InBuffer && OutBuffer)
    {
        const float* InBufferEnd = InBuffer+NumFrames;
        while(InBuffer<InBufferEnd)
        {
            *OutBuffer = m_EnvelopeFollower(*InBuffer);
            ++InBuffer;
            ++OutBuffer;
        }
    }
    else if(OutBuffer)
    {
        std::fill(OutBuffer, OutBuffer + NumFrames, 0.0f);
    }

    return 0;
}

void CEnvelopeFollowerFilter::SetAttack(float AttackMilliSeconds)
{
    m_EnvelopeFollower.SetAttack(AttackMilliSeconds);
}

void CEnvelopeFollowerFilter::SetRelease(float ReleaseMilliSeconds)
{
    m_EnvelopeFollower.SetRelease(ReleaseMilliSeconds);
}
