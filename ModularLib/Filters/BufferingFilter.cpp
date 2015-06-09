#include "BufferingFilter.h"


CBufferingFilter::CBufferingFilter(int SamplingFrequency, int CapacityMilliSeconds, const std::vector<std::string>& InputNames)
 : m_InputNames(InputNames)
 , m_Buffers()
{
    int Capacity = CapacityMilliSeconds*SamplingFrequency/1000;
    while(m_Buffers.size()<m_InputNames.size())
    {
        m_Buffers.emplace_back(new CSimpleReadWriteBuffer<float>(Capacity));
    }
}

std::vector<std::string> CBufferingFilter::GetInputNames() const
{
    return m_InputNames;
}

std::vector<std::string> CBufferingFilter::GetOutputNames() const
{
    return {};
}

std::vector<std::string> CBufferingFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CBufferingFilter::GetMidiOutputNames() const
{
    return {};
}

int CBufferingFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                  const std::vector<void *> &/*DestinationBuffers*/,
                                  const std::vector<std::shared_ptr<IMidiRenderer> > /*MidiRenderers*/,
                                  const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                  int NumFrames,
                                  std::uint32_t /*TimeStamp*/)
{
    for(int idx = 0; idx<static_cast<int>(m_Buffers.size()); ++idx)
    {
        if(SourceBuffers[idx])
        {
            m_Buffers[idx]->Write(static_cast<const float*>(SourceBuffers[idx]), NumFrames);
        }
    }

    return 0;
}

int CBufferingFilter::ReadBuffer(int idxBuffer, float *Destination, int Size)
{
    if(0<=idxBuffer && idxBuffer<static_cast<int>(m_Buffers.size()))
    {
        return m_Buffers[idxBuffer]->Read(Destination, Size);
    }

    return 0;
}
