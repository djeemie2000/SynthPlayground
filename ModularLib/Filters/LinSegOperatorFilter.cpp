#include <algorithm>
#include "LinSegOperatorFilter.h"
#include "LinSegOperator.h"

CLinSegOperatorFilter::CLinSegOperatorFilter()
{
}

std::vector<std::string> CLinSegOperatorFilter::GetInputNames() const
{
    return { "Phase", "A", "B", "C", "D" };
}

std::vector<std::string> CLinSegOperatorFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CLinSegOperatorFilter::GetMidiInputNames() const
{
    return {};
}

int CLinSegOperatorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* PhaseBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* ABuffer = static_cast<const float*>(SourceBuffers[1]);
    const float* BBuffer = static_cast<const float*>(SourceBuffers[2]);
    const float* CBuffer = static_cast<const float*>(SourceBuffers[3]);
    const float* DBuffer = static_cast<const float*>(SourceBuffers[4]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(PhaseBuffer && ABuffer && BBuffer && CBuffer && DBuffer && OutBuffer)
    {
        CLinSegOperator<float> Op;
        const float*PhaseBufferEnd = PhaseBuffer + NumFrames;
        while(PhaseBuffer<PhaseBufferEnd)
        {
            *OutBuffer = Op(*PhaseBuffer, *ABuffer, *BBuffer, *CBuffer, *DBuffer);
            ++PhaseBuffer;
            ++ABuffer;
            ++BBuffer;
            ++CBuffer;
            ++DBuffer;
            ++OutBuffer;
        }
    }
    else if(OutBuffer)
    {
        std::fill(OutBuffer, OutBuffer + NumFrames, 0.0f);
    }

    return 0;
}
