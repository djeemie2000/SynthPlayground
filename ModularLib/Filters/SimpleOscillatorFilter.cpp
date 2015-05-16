#include <algorithm>
#include "SimpleOscillatorFilter.h"
#include "Trigger.h"

CSimpleOscillatorFilter::CSimpleOscillatorFilter(int SamplingFrequency)
    : m_Oscillator(SamplingFrequency)
    , m_DefaultFreq()
    , m_DefaultSync()
    , m_DefaultSoftSync()
{
}

std::vector<std::string> CSimpleOscillatorFilter::GetInputNames() const
{
    return {"Freq", "Sync", "SoftSync"};
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
                                       const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                       int NumFrames,
                                       std::uint32_t /*TimeStamp*/)
{
    if(float* PhaseBuffer = (float*)(DestinationBuffers[0]))
    {
        if(static_cast<int>(m_DefaultFreq.size())<NumFrames)
        {
            const float DefaultFreq = 220.0f;
            m_DefaultFreq.assign(NumFrames, DefaultFreq);
        }
        if(static_cast<int>(m_DefaultSync.size())<NumFrames)
        {
            const float DefaultSync = 0.0f;
            m_DefaultSync.assign(NumFrames, DefaultSync);
        }
        if(static_cast<int>(m_DefaultSoftSync.size())<NumFrames)
        {
            const float DefaultSync = 0.0f;
            m_DefaultSoftSync.assign(NumFrames, DefaultSync);
        }

        const float* FreqBuffer = SourceBuffers[0] ?  (const float*)(SourceBuffers[0]) : m_DefaultFreq.data();
        const float* FreqBufferEnd = FreqBuffer + NumFrames;
        const float* SyncBuffer = SourceBuffers[1] ? (const float*)(SourceBuffers[1]) : m_DefaultSync.data();
        const float* SoftSyncBuffer = SourceBuffers[2] ? (const float*)(SourceBuffers[2]) : m_DefaultSoftSync.data();

        CTriggerIn<float> TriggerIn;

        while(FreqBuffer<FreqBufferEnd)
        {
            if(TriggerIn.IsTriggerOn(*SyncBuffer))//only sync upon start trigger!
            {
                m_Oscillator.Sync();
            }
            if(TriggerIn.IsTriggerOn(*SoftSyncBuffer))
            {
                m_Oscillator.SoftSync();
            }
            *PhaseBuffer = m_Oscillator(*FreqBuffer);
            ++FreqBuffer;
            ++SyncBuffer;
            ++SoftSyncBuffer;
            ++PhaseBuffer;
        }
    }

    return 0;
}

void CSimpleOscillatorFilter::SelectWaveform(int Selection)
{
    m_Oscillator.SelectWaveform(Selection);
}
