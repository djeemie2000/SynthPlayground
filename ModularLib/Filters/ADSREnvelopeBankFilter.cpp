#include <algorithm>
#include "ADSREnvelopeBankFilter.h"

CADSREnvelopeBankFilter::CADSREnvelopeBankFilter(int Size, int SamplingFrequency)
 : m_NumSamples(static_cast<float>(SamplingFrequency))
 , m_Envelope(Size)
{
}

std::vector<std::string> CADSREnvelopeBankFilter::GetInputNames() const
{
    std::vector<std::string> Names;
    for(std::size_t idx = 0; idx<m_Envelope.size(); ++idx)
    {
        Names.push_back("Trigger"+std::to_string(idx));
    }
    return Names;
}

std::vector<std::string> CADSREnvelopeBankFilter::GetOutputNames() const
{
    std::vector<std::string> Names;
    for(std::size_t idx = 0; idx<m_Envelope.size(); ++idx)
    {
        Names.push_back("Envelope"+std::to_string(idx));
    }
    return Names;
}

std::vector<std::string> CADSREnvelopeBankFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CADSREnvelopeBankFilter::GetMidiOutputNames() const
{
    return {};
}

int CADSREnvelopeBankFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    for(std::size_t idx = 0; idx<m_Envelope.size(); ++idx)
    {
        float* SrcBuffer = static_cast<float*>(SourceBuffers[idx]);
        float* DstBuffer = static_cast<float*>(DestinationBuffers[idx]);
        if(SrcBuffer && DstBuffer)
        {
            const float* DstBufferEnd = DstBuffer + NumFrames;
            while(DstBuffer<DstBufferEnd)
            {
                if(0.99f<*SrcBuffer)
                {
                    m_Envelope[idx].NoteOn();
                }
                else if(*SrcBuffer<-0.99f)
                {
                    m_Envelope[idx].NoteOff();
                }
                *DstBuffer = m_Envelope[idx]();
                ++SrcBuffer;
                ++DstBuffer;
            }
        }
        else if(DstBuffer)
        {
            std::fill(DstBuffer, DstBuffer + NumFrames, 0.0f);
        }
    }

    return 0;
}

void CADSREnvelopeBankFilter::SetAttackMilliSeconds(int Index, float Attack)
{
    m_NumSamples.SetMilliSeconds(Attack);
    m_Envelope[Index].SetAttackSamples(m_NumSamples());
}

void CADSREnvelopeBankFilter::SetDecayMilliSeconds(int Index, float Decay)
{
    m_NumSamples.SetMilliSeconds(Decay);
    m_Envelope[Index].SetDecaySamples(m_NumSamples());
}

void CADSREnvelopeBankFilter::SetSustain(int Index, float Sustain)
{
    m_Envelope[Index].SetSustain(Sustain);
}

void CADSREnvelopeBankFilter::SetReleaseMilliSeconds(int Index, float Release)
{
    m_NumSamples.SetMilliSeconds(Release);
    m_Envelope[Index].SetReleaseSamples(m_NumSamples());
}
