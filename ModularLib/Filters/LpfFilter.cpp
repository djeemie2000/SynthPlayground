#include <algorithm>
#include "LpfFilter.h"

CLpfFilter::CLpfFilter()
 : m_LPFilter()
{
}

std::vector<std::string> CLpfFilter::GetInputNames() const
{
    return { "In", "CutOff", "Res" };
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
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(OutBuffer)
    {
        const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
        const float* CutoffBuffer = static_cast<const float*>(SourceBuffers[1]);
        const float* ResBuffer = static_cast<const float*>(SourceBuffers[2]);
        if(InBuffer && CutoffBuffer && ResBuffer)
        {
            const float* InBufferEnd = InBuffer+NumFrames;
            while(InBuffer<InBufferEnd)
            {
                *OutBuffer = m_LPFilter(*InBuffer, *CutoffBuffer, *ResBuffer);
                ++InBuffer;
                ++CutoffBuffer;
                ++ResBuffer;
                ++OutBuffer;
            }
        }
        else if(InBuffer && CutoffBuffer)
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

void CLpfFilter::SetPoles(int Poles)
{
    m_LPFilter.SetStages(Poles);
}

void CLpfFilter::SetResonance(float Resonance)
{
    m_LPFilter.SetFeedback(Resonance);
}
