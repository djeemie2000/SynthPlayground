#include <algorithm>
#include <cmath>
#include "StereoMixerFilter.h"

CStereoMixerFilter::CStereoMixerFilter(int Size)
 : m_MasterVolume(1.0f)
 , m_Volume(Size, 0.0f)
 , m_Pan(Size, 0.0f)
{
}

std::vector<std::string> CStereoMixerFilter::GetInputNames() const
{
    std::vector<std::string> Names;
    for(std::size_t idx = 0; idx<m_Volume.size(); ++idx)
    {
        Names.push_back("In"+std::to_string(idx));
    }
    return Names;
}

std::vector<std::string> CStereoMixerFilter::GetOutputNames() const
{
    return { "OutL", "OutR" };
}

std::vector<std::string> CStereoMixerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CStereoMixerFilter::GetMidiOutputNames() const
{
    return {};
}

int CStereoMixerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
    { // left out
        std::fill(DstBuffer, DstBuffer + NumFrames, 0.0f);
        for(std::size_t idx = 0; idx<m_Volume.size(); ++idx)
        {
            if(float* SrcBuffer = static_cast<float*>(SourceBuffers[idx]))
            {
                float Amplification = ( 1 - std::max(0.0f, -m_Pan[idx]) )*m_Volume[idx];
                float* Dst = DstBuffer;
                const float* DstEnd = DstBuffer + NumFrames;
                while(Dst<DstEnd)
                {
                    *Dst += (*SrcBuffer)*Amplification;
                    ++SrcBuffer;
                    ++Dst;
                }
            }
        }
    }
    if(float* DstBuffer = static_cast<float*>(DestinationBuffers[1]))
    { // right out
        std::fill(DstBuffer, DstBuffer + NumFrames, 0.0f);
        for(std::size_t idx = 0; idx<m_Volume.size(); ++idx)
        {
            if(float* SrcBuffer = static_cast<float*>(SourceBuffers[idx]))
            {
                float Amplification = (1 - std::max(0.0f, m_Pan[idx]) )*m_Volume[idx];
                float* Dst = DstBuffer;
                const float* DstEnd = DstBuffer + NumFrames;
                while(Dst<DstEnd)
                {
                    *Dst += (*SrcBuffer)*Amplification;
                    ++SrcBuffer;
                    ++Dst;
                }
            }
        }
    }
    return 0;
}

void CStereoMixerFilter::SetMasterVolume(float Volume)
{
    m_MasterVolume = Volume;
}

void CStereoMixerFilter::SetVolume(int Index, float Volume)
{
    m_Volume[Index] = Volume;
}

void CStereoMixerFilter::SetPan(int Index, float Pan)
{
    m_Pan[Index] = Pan;
}
