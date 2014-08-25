#include <algorithm>
#include "ConstFilter.h"

CConstFilter::CConstFilter()
 : m_Value(0)
{
}

std::vector<std::string> CConstFilter::GetInputNames() const
{
    return {};
}

std::vector<std::string> CConstFilter::GetOutputNames() const
{
    return {"Const"};
}

std::vector<std::string> CConstFilter::GetMidiInputNames() const
{
    return {};
}

int CConstFilter::OnProcess(const std::vector<void *> &/*SourceBuffers*/,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
    {
        std::fill(DstBuffer, DstBuffer+NumFrames, m_Value);
    }

    return 0;
}

void CConstFilter::Set(float Value)
{
    m_Value = Value;
}
