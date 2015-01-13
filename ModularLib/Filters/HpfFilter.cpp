#include <algorithm>
#include "HpfFilter.h"

CHpfFilter::CHpfFilter()
 : m_Hpfilter()
{
}

std::vector<std::string> CHpfFilter::GetInputNames() const
{
    return { "In", "CutOff", "Res" };
}

std::vector<std::string> CHpfFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CHpfFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CHpfFilter::GetMidiOutputNames() const
{
    return {};
}

int CHpfFilter::OnProcess(const std::vector<void *> &SourceBuffers,
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
                *OutBuffer = m_Hpfilter(*InBuffer, *CutoffBuffer, *ResBuffer);
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
                *OutBuffer = m_Hpfilter(*InBuffer, *CutoffBuffer);
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

void CHpfFilter::SetPoles(int Poles)
{
    m_Hpfilter.SetStages(Poles);
}

void CHpfFilter::SetResonance(float Resonance)
{
    m_Hpfilter.SetFeedback(Resonance);
}
