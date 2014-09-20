#include <algorithm>
#include "NoiseFilter.h"

CNoiseFilter::CNoiseFilter()
 : m_Noise()
{
}

std::vector<std::string> CNoiseFilter::GetInputNames() const
{
    return { };
}

std::vector<std::string> CNoiseFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CNoiseFilter::GetMidiInputNames() const
{
    return {};
}

int CNoiseFilter::OnProcess(const std::vector<void *> &/*SourceBuffers*/,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    if(float* OutBuffer = static_cast<float*>(DestinationBuffers[0]))
    {
        const float* OutBufferEnd = OutBuffer + NumFrames;
        while(OutBuffer<OutBufferEnd)
        {
            *OutBuffer = m_Noise();
            ++OutBuffer;
        }
    }

    return 0;
}
