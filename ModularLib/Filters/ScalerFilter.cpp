#include <algorithm>
#include "ScalerFilter.h"
#include "Scaler.h"

CScalerFilter::CScalerFilter()
 : m_Scaler()
{
}

std::vector<std::string> CScalerFilter::GetInputNames() const
{
    return { "In", "Scale", "Offset" };
}

std::vector<std::string> CScalerFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CScalerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CScalerFilter::GetMidiOutputNames() const
{
    return {};
}

int CScalerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStScaler*/)
{
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(OutBuffer)
    {
        const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
        const float* ScaleBuffer = static_cast<const float*>(SourceBuffers[1]);
        const float* OffsetBuffer = static_cast<const float*>(SourceBuffers[2]);
        if(InBuffer && ScaleBuffer && OffsetBuffer)
        {
            const float* InBufferEnd = InBuffer + NumFrames;
            while(InBuffer<InBufferEnd)
            {
                *OutBuffer = m_Scaler(*InBuffer, *ScaleBuffer, *OffsetBuffer);
                ++InBuffer;
                ++ScaleBuffer;
                ++OffsetBuffer;
                ++OutBuffer;
            }
        }
        else if(InBuffer && ScaleBuffer)
        {
            const float* InBufferEnd = InBuffer + NumFrames;
            while(InBuffer<InBufferEnd)
            {
                *OutBuffer = m_Scaler(*InBuffer, *ScaleBuffer, 0.0f);
                ++InBuffer;
                ++ScaleBuffer;
                ++OutBuffer;
            }
        }
        if(InBuffer && OffsetBuffer)
        {
            const float* InBufferEnd = InBuffer + NumFrames;
            while(InBuffer<InBufferEnd)
            {
                *OutBuffer = m_Scaler(*InBuffer, 1.0f, *OffsetBuffer);
                ++InBuffer;
                ++OffsetBuffer;
                ++OutBuffer;
            }
        }
        else if(InBuffer)
        {
            std::copy(InBuffer, InBuffer+NumFrames, OutBuffer);
        }

    }

    return 0;
}
