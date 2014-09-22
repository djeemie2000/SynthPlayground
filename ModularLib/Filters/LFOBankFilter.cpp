#include <algorithm>
#include "LFOBankFilter.h"
#include "SelectableOperatorFactory.h"

CLFOBankFilter::CLFOBankFilter(int Size, int SamplingFrequency)
 : m_LFO(Size, {static_cast<float>(SamplingFrequency), CSelectableOperatorFactory::Create()})
{
}

std::vector<std::string> CLFOBankFilter::GetInputNames() const
{
    return {};
}

std::vector<std::string> CLFOBankFilter::GetOutputNames() const
{
    std::vector<std::string> Names;
    for(std::size_t idx = 0; idx<m_LFO.size(); ++idx)
    {
        Names.push_back("LFO"+std::to_string(idx));
    }
    return Names;
}

std::vector<std::string> CLFOBankFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CLFOBankFilter::GetMidiOutputNames() const
{
    return {};
}

int CLFOBankFilter::OnProcess(const std::vector<void *> &/*SourceBuffers*/,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    for(std::size_t idx = 0; idx<m_LFO.size(); ++idx)
    {
        if(float* DstBuffer = static_cast<float*>(DestinationBuffers[idx]))
        {
            //std::generate(DstBuffer, DstBuffer+NumFrames, m_LFO[idx]);
            const float* DstBufferEnd = DstBuffer + NumFrames;
            while(DstBuffer<DstBufferEnd)
            {
                *DstBuffer = m_LFO[idx]();
                ++DstBuffer;
            }
        }
    }

    return 0;
}

void CLFOBankFilter::SetFrequency(int Index, float Frequency)
{
    m_LFO[Index].SetFrequency(Frequency);
}

void CLFOBankFilter::Select(int Index, int Selection)
{
    m_LFO[Index].SelectWaveform(Selection);
}
