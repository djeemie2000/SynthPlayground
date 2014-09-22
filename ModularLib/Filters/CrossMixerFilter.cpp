#include <algorithm>
#include "CrossMixerFilter.h"

CCrossMixerFilter::CCrossMixerFilter()
 : m_Mixer()
{
}

std::vector<std::string> CCrossMixerFilter::GetInputNames() const
{
    return { "In1", "In2", "Mix" };
}

std::vector<std::string> CCrossMixerFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CCrossMixerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CCrossMixerFilter::GetMidiOutputNames() const
{
    return {};
}

int CCrossMixerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* In1Buffer = static_cast<const float*>(SourceBuffers[0]);
    const float* In2Buffer = static_cast<const float*>(SourceBuffers[1]);
    const float* MixBuffer = static_cast<const float*>(SourceBuffers[2]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(In1Buffer && In2Buffer && OutBuffer && MixBuffer)
    {
        const float* MixBufferEnd = MixBuffer + NumFrames;
        while(MixBuffer<MixBufferEnd)
        {
            *OutBuffer = m_Mixer(*In1Buffer, *In2Buffer, *MixBuffer);
            ++In1Buffer;
            ++In2Buffer;
            ++MixBuffer;
            ++OutBuffer;
        }
    }

    return 0;
}
