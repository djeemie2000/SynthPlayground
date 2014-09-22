#include <algorithm>
#include "MixerFilter.h"

CMixerFilter::CMixerFilter(int Size)
 : m_MasterVolume(1.0f)
 , m_Volume(Size, 0.0f)
{
}

std::vector<std::string> CMixerFilter::GetInputNames() const
{
    std::vector<std::string> Names;
    for(std::size_t idx = 0; idx<m_Volume.size(); ++idx)
    {
        Names.push_back("In"+std::to_string(idx));
    }
    return Names;
}

std::vector<std::string> CMixerFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CMixerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CMixerFilter::GetMidiOutputNames() const
{
    return {};
}

int CMixerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
    {
        std::fill(DstBuffer, DstBuffer + NumFrames, 0.0f);
        for(std::size_t idx = 0; idx<m_Volume.size(); ++idx)
        {
            if(float* SrcBuffer = static_cast<float*>(SourceBuffers[idx]))
            {
                float* Dst = DstBuffer;
                const float* DstEnd = DstBuffer + NumFrames;
                while(Dst<DstEnd)
                {
                    *Dst += (*SrcBuffer)*m_Volume[idx]*m_MasterVolume;
                    ++SrcBuffer;
                    ++Dst;
                }
            }
        }
    }
    return 0;
}

void CMixerFilter::SetMasterVolume(float Volume)
{
    m_MasterVolume = Volume;
}

void CMixerFilter::SetVolume(int Index, float Volume)
{
    m_Volume[Index] = Volume;
}
