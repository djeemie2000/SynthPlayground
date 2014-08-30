#include <algorithm>
#include "PhasorFilter.h"

CPhasorFilter::CPhasorFilter(int SamplingFrequency)
    : m_PhaseStep(SamplingFrequency)
    , m_PhaseGenerator()
{
}

std::vector<std::string> CPhasorFilter::GetInputNames() const
{
    return {"Freq", "Sync"};
}

std::vector<std::string> CPhasorFilter::GetOutputNames() const
{
    return {"Phase"};
}

std::vector<std::string> CPhasorFilter::GetMidiInputNames() const
{
    return {};
}

int CPhasorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                             const std::vector<void *> &DestinationBuffers,
                             const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                             int NumFrames,
                             std::uint32_t /*TimeStamp*/)
{
    const float* FreqBuffer = (const float*)(SourceBuffers[0]);
    const float* FreqBufferEnd = FreqBuffer + NumFrames;
    const float* SyncBuffer = (const float*)(SourceBuffers[1]);
    float* PhaseBuffer = (float*)(DestinationBuffers[0]);
    if(FreqBuffer && PhaseBuffer)
    {
        if(SyncBuffer)
        {
            while(FreqBuffer<FreqBufferEnd)
            {
                if(*SyncBuffer!=0.0f)
                {
                    m_PhaseGenerator.Sync();
                }
                *PhaseBuffer = m_PhaseGenerator(m_PhaseStep(*FreqBuffer));
                ++FreqBuffer;
                ++SyncBuffer;
                ++PhaseBuffer;
            }
        }
        else
        {
            while(FreqBuffer<FreqBufferEnd)
            {
                *PhaseBuffer = m_PhaseGenerator(m_PhaseStep(*FreqBuffer));
                ++FreqBuffer;
                ++PhaseBuffer;
            }

        }
    }

    return 0;
}
