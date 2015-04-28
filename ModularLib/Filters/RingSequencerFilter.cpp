#include <algorithm>
#include "RingSequencerFilter.h"
#include "RingSequencer.h"
#include "Trigger.h"

CRingSequencerFilter::CRingSequencerFilter()
    : m_RingSequencer()
    , m_DefaultTrigger()
    , m_DefaultStep()
{
}

std::vector<std::string> CRingSequencerFilter::GetInputNames() const
{
    return { "Trigger", "Step" };
}

std::vector<std::string> CRingSequencerFilter::GetOutputNames() const
{
    return { "CV" };
}

std::vector<std::string> CRingSequencerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CRingSequencerFilter::GetMidiOutputNames() const
{
    return {};
}

int CRingSequencerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                       const std::vector<void *> &DestinationBuffers,
                                       const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                       const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                       int NumFrames,
                                       std::uint32_t /*TimeStamp*/)
{
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(OutBuffer)
    {
        if(static_cast<int>(m_DefaultTrigger.size())<NumFrames)
        {
            const float DefaultTrigger = 0.0f;
            m_DefaultTrigger.assign(NumFrames, DefaultTrigger);
        }
        if(static_cast<int>(m_DefaultStep.size())<NumFrames)
        {
            const float DefaultDecr = 0.27f;
            m_DefaultStep.assign(NumFrames, DefaultDecr);
        }

        const float* TriggerBuffer = SourceBuffers[0] ? static_cast<const float*>(SourceBuffers[0]) : m_DefaultTrigger.data();
        const float* StepBuffer = SourceBuffers[1] ? static_cast<const float*>(SourceBuffers[1]) : m_DefaultStep.data();

        CTriggerIn<float> TriggerIn;

        const float* StepBufferEnd = StepBuffer + NumFrames;
        while(StepBuffer<StepBufferEnd)
        {
            *OutBuffer = m_RingSequencer(TriggerIn.IsTriggerOn(*TriggerBuffer), *StepBuffer);
            ++TriggerBuffer;
            ++StepBuffer;
            ++OutBuffer;
        }
    }

    return 0;
}
