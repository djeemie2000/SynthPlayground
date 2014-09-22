#include <algorithm>
#include "PosNegShaperFilter.h"

CPosNegShaperFilter::CPosNegShaperFilter()
 : m_Invert(false)
 , m_Inverter()
 , m_Derectifier()
{
}

std::vector<std::string> CPosNegShaperFilter::GetInputNames() const
{
    return { "In" };
}

std::vector<std::string> CPosNegShaperFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CPosNegShaperFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CPosNegShaperFilter::GetMidiOutputNames() const
{
    return {};
}

int CPosNegShaperFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(InBuffer && OutBuffer)
    {
        if(m_Invert)
        {
            const float* Src = InBuffer;
            const float* SrcEnd = InBuffer + NumFrames;
            float* Dst = OutBuffer;
            while(Src<SrcEnd)
            {
                *Dst = m_Derectifier(m_Inverter(-*Src));
                ++Src;
                ++Dst;
            }
        }
        else
        {
            const float* Src = InBuffer;
            const float* SrcEnd = InBuffer + NumFrames;
            float* Dst = OutBuffer;
            while(Src<SrcEnd)
            {
                *Dst = m_Derectifier(m_Inverter(*Src));
                ++Src;
                ++Dst;
            }
        }
    }
    else if(OutBuffer)
    {
        std::fill(OutBuffer, OutBuffer + NumFrames, 0.0f);
    }

    return 0;
}

void CPosNegShaperFilter::SetInvert(bool Invert)
{
    m_Invert = Invert;
}

void CPosNegShaperFilter::SetInverterMode(int Mode)
{
    // TODO use bitwise ands on Mode-1 : 00 01 10 11
    if(Mode == 1)
    {
        m_Inverter.SetPosInvert(false);
        m_Inverter.SetNegInvert(false);
    }
    else if(Mode == 2)
    {
        m_Inverter.SetPosInvert(false);
        m_Inverter.SetNegInvert(true);
    }
    else if(Mode == 3)
    {
        m_Inverter.SetPosInvert(true);
        m_Inverter.SetNegInvert(false);
    }
    else if(Mode == 4)
    {
        m_Inverter.SetPosInvert(true);
        m_Inverter.SetNegInvert(true);
    }
}

void CPosNegShaperFilter::SetDerectifierMode(int Mode)
{
    if(Mode == 1)
    {
        m_Derectifier.SetPosDerectify(false);
        m_Derectifier.SetNegDerectify(false);
    }
    else if(Mode == 2)
    {
        m_Derectifier.SetPosDerectify(false);
        m_Derectifier.SetNegDerectify(true);
    }
    else if(Mode == 3)
    {
        m_Derectifier.SetPosDerectify(true);
        m_Derectifier.SetNegDerectify(false);
    }
    else if(Mode == 4)
    {
        m_Derectifier.SetPosDerectify(true);
        m_Derectifier.SetNegDerectify(true);
    }
}
