#include <algorithm>
#include "SimpleOscillatorFilter.h"

CSimpleOscillatorFilter::CSimpleOscillatorFilter(int SamplingFrequency)
    : m_Oscillator(SamplingFrequency)
{
}

std::vector<std::string> CSimpleOscillatorFilter::GetInputNames() const
{
    return {"Freq", "Sync"};
}

std::vector<std::string> CSimpleOscillatorFilter::GetOutputNames() const
{
    return {"Out"};
}

std::vector<std::string> CSimpleOscillatorFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CSimpleOscillatorFilter::GetMidiOutputNames() const
{
    return {};
}

int CSimpleOscillatorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
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
                if(0.99<*SyncBuffer)//only sync upon start trigger!
                {
                    m_Oscillator.Sync();
                }
                *PhaseBuffer = m_Oscillator(*FreqBuffer);
                ++FreqBuffer;
                ++SyncBuffer;
                ++PhaseBuffer;
            }
        }
        else
        {
            while(FreqBuffer<FreqBufferEnd)
            {
                *PhaseBuffer = m_Oscillator(*FreqBuffer);
                ++FreqBuffer;
                ++PhaseBuffer;
            }

        }
    }

    return 0;
}

void CSimpleOscillatorFilter::SelectWaveform(int Selection)
{
    m_Oscillator.SelectWaveform(Selection);
}
