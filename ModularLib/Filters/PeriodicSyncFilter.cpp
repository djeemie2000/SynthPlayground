#include <algorithm>
#include "PeriodicSyncFilter.h"

CPeriodicSyncFilter::CPeriodicSyncFilter(int SamplingFrequency)
    : m_Trigger(SamplingFrequency)
{
}

std::vector<std::string> CPeriodicSyncFilter::GetInputNames() const
{
    return {"Freq"};
}

std::vector<std::string> CPeriodicSyncFilter::GetOutputNames() const
{
    return {"Sync"};
}

std::vector<std::string> CPeriodicSyncFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CPeriodicSyncFilter::GetMidiOutputNames() const
{
    return {};
}

int CPeriodicSyncFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                   const std::vector<void *> &DestinationBuffers,
                                   const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                   int NumFrames,
                                   std::uint32_t /*TimeStamp*/)
{
    const float* FreqBuffer = (const float*)(SourceBuffers[0]);
    float* SyncBuffer = (float*)(DestinationBuffers[0]);
    if(FreqBuffer && SyncBuffer)
    {
        const float* FreqBufferEnd = FreqBuffer + NumFrames;
        while(FreqBuffer<FreqBufferEnd)
        {
            *SyncBuffer = m_Trigger(*FreqBuffer);
            ++FreqBuffer;
            ++SyncBuffer;
        }
    }

    return 0;
}
