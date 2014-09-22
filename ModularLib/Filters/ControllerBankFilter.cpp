#include <algorithm>
#include "ControllerBankFilter.h"

CControllerBankFilter::CControllerBankFilter(int Size)
 : m_Value(Size, 0)
{
}

std::vector<std::string> CControllerBankFilter::GetInputNames() const
{
    return {};
}

std::vector<std::string> CControllerBankFilter::GetOutputNames() const
{
    std::vector<std::string> Names;
    for(std::size_t idx = 0; idx<m_Value.size(); ++idx)
    {
        Names.push_back("Contr"+std::to_string(idx));
    }
    return Names;
}

std::vector<std::string> CControllerBankFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CControllerBankFilter::GetMidiOutputNames() const
{
    return {};
}

int CControllerBankFilter::OnProcess(const std::vector<void *> &/*SourceBuffers*/,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    for(std::size_t idx = 0; idx<m_Value.size(); ++idx)
    {
        if(float* DstBuffer = static_cast<float*>(DestinationBuffers[idx]))
        {
            std::fill(DstBuffer, DstBuffer+NumFrames, m_Value[idx]);
        }
    }

    return 0;
}

void CControllerBankFilter::Set(int Index, float Value)
{
    m_Value[Index] = Value;
}
