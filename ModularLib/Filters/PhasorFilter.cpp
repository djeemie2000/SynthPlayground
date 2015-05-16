#include <algorithm>
#include "PhasorFilter.h"
#include "Trigger.h"

CPhasorFilter::CPhasorFilter(int SamplingFrequency)
    : m_PhaseStep(SamplingFrequency)
    , m_PhaseAccumulator()
    , m_PhaseStepSign(1.0f)
    , m_DefaultFreq()
    , m_DefaultSync()
    , m_DefaultSoftSync()
{
}

std::vector<std::string> CPhasorFilter::GetInputNames() const
{
    return {"Freq", "Sync", "SoftSync"};
}

std::vector<std::string> CPhasorFilter::GetOutputNames() const
{
    return {"Phase"};
}

std::vector<std::string> CPhasorFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CPhasorFilter::GetMidiOutputNames() const
{
    return {};
}

int CPhasorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                             const std::vector<void *> &DestinationBuffers,
                             const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                             const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                             int NumFrames,
                             std::uint32_t /*TimeStamp*/)
{
    if(float* PhaseBuffer = static_cast<float*>(DestinationBuffers[0]))
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
                m_PhaseAccumulator.Sync();
            }
            if(TriggerIn.IsTriggerOn(*SoftSyncBuffer))
            {
                // invert phase step
                m_PhaseStepSign = -m_PhaseStepSign;
            }
            *PhaseBuffer = m_PhaseAccumulator(m_PhaseStepSign*m_PhaseStep(*FreqBuffer));
            ++FreqBuffer;
            ++SyncBuffer;
            ++SoftSyncBuffer;
            ++PhaseBuffer;
        }
    }

    return 0;
}
