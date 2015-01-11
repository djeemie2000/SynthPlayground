#include <algorithm>
#include <string>
#include "ExtendedModulatorFilter.h"
#include "Conversions.h"

CExtendedModulatorFilter::CExtendedModulatorFilter(int Size)
 : m_Size(Size)
{
}

std::vector<std::string> CExtendedModulatorFilter::GetInputNames() const
{
    std::vector<std::string> Names;
    Names.push_back("ModOffset");
    for(int idx = 0; idx<m_Size; ++idx)
    {
        Names.push_back("ModIn"+std::to_string(idx));
        Names.push_back("ModAmt"+std::to_string(idx));
    }
    return Names;
}

std::vector<std::string> CExtendedModulatorFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CExtendedModulatorFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CExtendedModulatorFilter::GetMidiOutputNames() const
{
    return {};
}

int CExtendedModulatorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
    {
        if(const float* ModOffsetBuffer = static_cast<const float*>(SourceBuffers[0]))
        {
            std::copy(ModOffsetBuffer, ModOffsetBuffer + NumFrames, DstBuffer);
        }
        else
        {
            std::fill(DstBuffer, DstBuffer + NumFrames, 0.0f);
        }

        for(int idx = 0; idx<m_Size; ++idx)
        {
            const float* ModInBuffer = static_cast<const float*>(SourceBuffers[1+idx*2]);
            const float* ModAmtBuffer = static_cast<const float*>(SourceBuffers[2+idx*2]);
            if(ModInBuffer && ModAmtBuffer)
            {
                float* Dst = DstBuffer;
                const float* DstEnd = DstBuffer + NumFrames;
                while(Dst<DstEnd)
                {
                    *Dst += (*ModInBuffer)*(*ModAmtBuffer);
                    ++ModInBuffer;
                    ++ModAmtBuffer;
                    ++Dst;
                }
            }
        }
    }
    return 0;
}
