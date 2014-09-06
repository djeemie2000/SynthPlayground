#include <algorithm>
#include "ModulatorFilter.h"
#include "Conversions.h"

CModulatorFilter::CModulatorFilter(int Size)
 : m_Offset(0.0f)
 , m_ModAmt(Size, 0.0f)
 , m_LimitMode(1)
{
}

std::vector<std::string> CModulatorFilter::GetInputNames() const
{
    std::vector<std::string> Names;
    for(std::size_t idx = 0; idx<m_ModAmt.size(); ++idx)
    {
        Names.push_back("ModIn"+std::to_string(idx));
    }
    return Names;
}

std::vector<std::string> CModulatorFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CModulatorFilter::GetMidiInputNames() const
{
    return {};
}

int CModulatorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
    {
        std::fill(DstBuffer, DstBuffer + NumFrames, m_Offset);
        for(std::size_t idx = 0; idx<m_ModAmt.size(); ++idx)
        {
            if(float* SrcBuffer = static_cast<float*>(SourceBuffers[idx]))
            {
                float* Dst = DstBuffer;
                const float* DstEnd = DstBuffer + NumFrames;
                while(Dst<DstEnd)
                {
                    *Dst += (*SrcBuffer)*m_ModAmt[idx];
                    ++SrcBuffer;
                    ++Dst;
                }
            }
        }
        if(m_LimitMode==1)
        {
            float* Dst = DstBuffer;
            const float* DstEnd = DstBuffer + NumFrames;
            while(Dst<DstEnd)
            {
                CropSigned(*Dst);
                ++Dst;
            }
        }
        else if(m_LimitMode==2)
        {
            float* Dst = DstBuffer;
            const float* DstEnd = DstBuffer + NumFrames;
            while(Dst<DstEnd)
            {
                CropUnsigned(*Dst);
                ++Dst;
            }
        }
    }
    return 0;
}

void CModulatorFilter::SetOffset(float Offset)
{
    m_Offset = Offset;
}

void CModulatorFilter::SetLimitMode(int Mode)
{
    m_LimitMode = Mode;
}

void CModulatorFilter::SetModAmt(int Index, float ModAmt)
{
    m_ModAmt[Index] = ModAmt;
}
