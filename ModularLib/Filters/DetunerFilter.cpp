#include <algorithm>
#include "DetunerFilter.h"

CDetunerFilter::CDetunerFilter(int Size)
 : m_Detuner(Size)
{
}

std::vector<std::string> CDetunerFilter::GetInputNames() const
{
    return {"Freq"};
}

std::vector<std::string> CDetunerFilter::GetOutputNames() const
{
    std::vector<std::string> Names;
    for(std::size_t idx = 0; idx<m_Detuner.size(); ++idx)
    {
        Names.push_back("Freq"+std::to_string(idx));
    }
    return Names;
}

std::vector<std::string> CDetunerFilter::GetMidiInputNames() const
{
    return {};
}

int CDetunerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    if(const float* FreqBuffer = static_cast<const float*>(SourceBuffers[0]))
    {
        for(std::size_t idx = 0; idx<m_Detuner.size(); ++idx)
        {
            if(float* DstBuffer = static_cast<float*>(DestinationBuffers[idx]))
            {
                const float* Freq = FreqBuffer;
                const float* DstBufferEnd = DstBuffer + NumFrames;
                while(DstBuffer<DstBufferEnd)
                {
                    *DstBuffer = m_Detuner[idx](*Freq);
                    ++Freq;
                    ++DstBuffer;
                }
            }
        }
    }
    else
    {
        for(std::size_t idx = 0; idx<m_Detuner.size(); ++idx)
        {
            if(float* DstBuffer = static_cast<float*>(DestinationBuffers[idx]))
            {
                std::fill(DstBuffer, DstBuffer + NumFrames, 440.0f);//default freq???
            }
        }
    }

    return 0;
}

void CDetunerFilter::SetDetune(int Index, float Detune)
{
    m_Detuner[Index].SetDetune(Detune);
}

void CDetunerFilter::SetOctaveShift(int Index, int OctaveShift)
{
    m_Detuner[Index].SetOctaveShift(OctaveShift);
}
