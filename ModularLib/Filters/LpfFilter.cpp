#include <algorithm>
#include "LpfFilter.h"

CLpfFilter::CLpfFilter()
 : m_LPFilter()
{
}

std::vector<std::string> CLpfFilter::GetInputNames() const
{
    return { "In", "CutOff" };
}

std::vector<std::string> CLpfFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CLpfFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CLpfFilter::GetMidiOutputNames() const
{
    return {};
}

int CLpfFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* CutoffBuffer = static_cast<const float*>(SourceBuffers[1]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(InBuffer && CutoffBuffer && OutBuffer)
    {
        //std::transform(InBuffer, InBuffer+NumFrames, CutoffBuffer, OutBuffer, m_LPFilter); -> uses a copy of m_LPFilter?
        const float* InBufferEnd = InBuffer+NumFrames;
        while(InBuffer<InBufferEnd)
        {
            *OutBuffer = m_LPFilter(*InBuffer, *CutoffBuffer);
            ++InBuffer;
            ++CutoffBuffer;
            ++OutBuffer;
        }
    }

    return 0;
}

void CLpfFilter::SetPoles(int Poles)
{
    m_LPFilter.SetStages(Poles);
}

void CLpfFilter::SetResonance(float Resonance)
{
    m_LPFilter.SetFeedback(Resonance);
}
