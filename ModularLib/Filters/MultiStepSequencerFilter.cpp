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
    float* GateOutBuffer = (float*)(DestinationBuffers[2]);
    float* TriggerOutBuffer = (float*)(DestinationBuffers[3]);

    if(ClockInBuffer)
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

            // this is not the optimal way, but works correctly
            if(FreqOutBuffer)
            {
                *FreqOutBuffer = m_Frequency;
                ++FreqOutBuffer;
            }
            if(VelocityOutBuffer)
            {
                *VelocityOutBuffer = m_Velocity;
                ++VelocityOutBuffer;
            }
            if(GateOutBuffer)
            {
                *GateOutBuffer = m_Gate;
                ++GateOutBuffer;
            }
            if(TriggerOutBuffer)
            {
                *TriggerOutBuffer = m_GateToTrigger(m_Gate);
                ++TriggerOutBuffer;
            }

            ++ClockInBuffer;
        }
    }
    else
    { // no clock in => no change
        if(FreqOutBuffer)
        {
            std::fill(FreqOutBuffer, FreqOutBuffer+NumFrames, m_Frequency);
        }
        if(VelocityOutBuffer)
        {
            std::fill(VelocityOutBuffer, VelocityOutBuffer+NumFrames, m_Velocity);
        }
        if(GateOutBuffer)
        {
            std::fill(GateOutBuffer, GateOutBuffer+NumFrames, m_Gate);
        }
        if(TriggerOutBuffer)
        {
            std::fill(TriggerOutBuffer, TriggerOutBuffer+NumFrames, 0);
        }
    }

    //?? here ??
    m_Callback(m_MultiStepSequencer.GetCurrentStep());

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

void CMultiStepSequencerFilter::SetVelocity(int Step, int Velocity)
{
    m_MultiStepSequencer.SetVelocity(Step, Velocity);
}

void CMultiStepSequencerFilter::SetDuration(int Step, int Duration)
{
    m_MultiStepSequencer.SetDuration(Step, Duration);
}

void CMultiStepSequencerFilter::SetNumSubSteps(int Step, int NumSubSteps)
{
    m_MultiStepSequencer.SetNumSubSteps(Step, NumSubSteps);
}

void CMultiStepSequencerFilter::SetSubStepMode(int Step, int Mode)
{
    CMultiStepSequencer<float, NumSequencerSteps>::ESubStepGateMode StepMode = static_cast< CMultiStepSequencer<float, NumSequencerSteps>::ESubStepGateMode >(Mode);
    m_MultiStepSequencer.SetSubStepMode(Step, StepMode);
}

void CMultiStepSequencerFilter::SetNote(int Step, ENote Note)
{
    m_MultiStepSequencer.SetNote(Step, Note);
}

void CMultiStepSequencerFilter::SetStepSize(int StepSize)
{
    m_MultiStepSequencer.SetStepSize(StepSize);
}

void CMultiStepSequencerFilter::SetStepIntervalBegin(int Step)
{
    m_MultiStepSequencer.SetStepIntervalBegin(Step);
}

void CMultiStepSequencerFilter::SetActive(bool /*Active*/)
{
//    m_IsActive = Active;
}

void CMultiStepSequencerFilter::SetStepIntervalLength(int Length)
{
    m_MultiStepSequencer.SetStepIntervalLength(Length);
}
