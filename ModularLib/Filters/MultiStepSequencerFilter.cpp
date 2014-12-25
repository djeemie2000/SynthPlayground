#include <algorithm>
#include "MultiStepSequencerFilter.h"

CMultiStepSequencerFilter::CMultiStepSequencerFilter(int SamplingFrequency, CurrentStepCallbackType Callback)
    : m_ClockIn()
    , m_MultiStepSequencer()
    , m_GateToTrigger()
//    , m_IsActive(false)
    , m_Gate(0.0f)
    , m_Frequency(110.0f)
    , m_Velocity(1.0f)
    , m_Callback(Callback)
{
}

std::vector<std::string> CMultiStepSequencerFilter::GetInputNames() const
{
    return {"Clock"};
}

std::vector<std::string> CMultiStepSequencerFilter::GetOutputNames() const
{
    return {"Vel", "Freq", "Gate", "Trigger"};
}

std::vector<std::string> CMultiStepSequencerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CMultiStepSequencerFilter::GetMidiOutputNames() const
{
    return {};
}

int CMultiStepSequencerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                   const std::vector<void *> &DestinationBuffers,
                                   const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                   const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                   int NumFrames,
                                   std::uint32_t /*TimeStamp*/)
{
    const float* ClockInBuffer = (const float*)(SourceBuffers[0]);
    float* VelocityOutBuffer = (float*)(DestinationBuffers[0]);
    float* FreqOutBuffer = (float*)(DestinationBuffers[1]);
    float* TriggerOutBuffer = (float*)(DestinationBuffers[2]);
    float* GateOutBuffer = (float*)(DestinationBuffers[3]);

    if(ClockInBuffer && GateOutBuffer && FreqOutBuffer && TriggerOutBuffer)
    {
        const float* ClockInBufferEnd = ClockInBuffer + NumFrames;
        while(ClockInBuffer<ClockInBufferEnd)
        {
            if(m_ClockIn.RisingEdge(*ClockInBuffer))
            {
                m_MultiStepSequencer.AdvanceClock();
                // these values can only change upon advance clock of the sequencer!
                m_Frequency = m_MultiStepSequencer.GetFrequency();
                m_Velocity = m_MultiStepSequencer.GetVelocity();
                m_Gate = m_MultiStepSequencer.GetGate();
            }

            *FreqOutBuffer = m_Frequency;
            *VelocityOutBuffer = m_Velocity;
            *GateOutBuffer = m_Gate;
            *TriggerOutBuffer = m_GateToTrigger(m_Gate);

            ++ClockInBuffer;
            ++FreqOutBuffer;
            ++VelocityOutBuffer;
            ++GateOutBuffer;
            ++TriggerOutBuffer;
        }
    }

    return 0;
}

int CMultiStepSequencerFilter::GetMaxNumSteps() const
{
    return m_MultiStepSequencer.GetMaxNumSteps();
}

void CMultiStepSequencerFilter::SetOctave(int Step, EOctave Octave)
{
    m_MultiStepSequencer.SetOctave(Step, Octave);
}

void CMultiStepSequencerFilter::SetStepMode(int Step, int Mode)
{
    CMultiStepSequencer<float, NumSequencerSteps>::EStepMode StepMode = static_cast< CMultiStepSequencer<float, NumSequencerSteps>::EStepMode >(Mode);
    m_MultiStepSequencer.SetStepMode(Step, StepMode);
}

void CMultiStepSequencerFilter::SetNote(int Step, ENote Note)
{
    m_MultiStepSequencer.SetNote(Step, Note);
}

void CMultiStepSequencerFilter::SetStepSize(int StepSize)
{
    m_MultiStepSequencer.SetStepSize(StepSize);
}

void CMultiStepSequencerFilter::SetActive(bool /*Active*/)
{
//    m_IsActive = Active;
}

void CMultiStepSequencerFilter::SetStepIntervalLength(int Length)
{
    m_MultiStepSequencer.SetStepIntervalLength(Length);
}
