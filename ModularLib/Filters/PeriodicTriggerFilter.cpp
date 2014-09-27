#include <algorithm>
#include "PeriodicTriggerFilter.h"

CPeriodicTriggerFilter::CPeriodicTriggerFilter(int SamplingFrequency)
    : m_PeriodicTrigger(SamplingFrequency)
    , m_Counter(0)
{
    m_PeriodicTrigger.SetBeatsPerMinute(120);
    m_PeriodicTrigger.SetBarsPerBeat(1);
    m_PeriodicTrigger.SetDuration(100);
}

std::vector<std::string> CPeriodicTriggerFilter::GetInputNames() const
{
    return {};
}

std::vector<std::string> CPeriodicTriggerFilter::GetOutputNames() const
{
    return {"Trigger"};
}

std::vector<std::string> CPeriodicTriggerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CPeriodicTriggerFilter::GetMidiOutputNames() const
{
    return {};
}

int CPeriodicTriggerFilter::OnProcess(const std::vector<void *> &/*SourceBuffers*/,
                                   const std::vector<void *> &DestinationBuffers,
                                   const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                   const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                   int NumFrames,
                                   std::uint32_t /*TimeStamp*/)
{
    float* TriggerBuffer = (float*)(DestinationBuffers[0]);
    if(TriggerBuffer)
    {
        // handle case where duration is 100% => should trigger off!!!
        int DurationSamples = m_PeriodicTrigger.DurationSamples()-1;// -1 because of 100% duration case
        int PeriodSamples = m_PeriodicTrigger.PeriodSamples();
        const float* TriggerBufferEnd = TriggerBuffer + NumFrames;
        while(TriggerBuffer<TriggerBufferEnd)
        {
            *TriggerBuffer = 0;
            if(0==m_Counter)
            {
                *TriggerBuffer = 1.0f;
            }
            else if(DurationSamples==m_Counter)
            {
                *TriggerBuffer = -1.0f;
            }

            ++TriggerBuffer;

            ++m_Counter;
            if(PeriodSamples<=m_Counter)
            {
                m_Counter = 0;
            }
        }
    }

    return 0;
}

void CPeriodicTriggerFilter::SetBeatsPerMinute(int Bpm)
{
    m_PeriodicTrigger.SetBeatsPerMinute(Bpm);
}

void CPeriodicTriggerFilter::SetBeatsPerBar(int Bpb)
{
    m_PeriodicTrigger.SetBarsPerBeat(Bpb);
}

void CPeriodicTriggerFilter::SetDuration(int DurationPercentage)
{
    m_PeriodicTrigger.SetDuration(DurationPercentage);
}
