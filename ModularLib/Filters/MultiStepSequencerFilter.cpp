#include <algorithm>
#include "MultiStepSequencerFilter.h"
#include "MidiNotePitch.h"
#include "MidiNoteConverter.h"

CMultiStepSequencerFilter::CMultiStepSequencerFilter(int SamplingFrequency, CurrentStepCallbackType Callback)
    : m_MultiStepSequencer(SamplingFrequency)
    , m_CurrentStep()
    , m_IsActive(false)
    , m_StepSize(1)
    , m_Frequency(440.0f)
    , m_Callback(Callback)
{
}

std::vector<std::string> CMultiStepSequencerFilter::GetInputNames() const
{
    return {"Clock"};
}

std::vector<std::string> CMultiStepSequencerFilter::GetOutputNames() const
{
    return {"Vel", "Freq", "Trigger"};
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
    const float* ClockBuffer = (const float*)(SourceBuffers[0]);
    float* VelocityOutBuffer = (float*)(DestinationBuffers[0]);
    float* FreqOutBuffer = (float*)(DestinationBuffers[1]);
    float* TriggerOutBuffer = (float*)(DestinationBuffers[2]);

    if(ClockBuffer && TriggerOutBuffer && FreqOutBuffer)
    {
        const float* TriggerInBufferEnd = ClockBuffer + NumFrames;
        while(ClockBuffer<TriggerInBufferEnd)
        {
            *TriggerOutBuffer = 0.0f;
            if(0.99f<*ClockBuffer)
            {
                m_MultiStepSequencer.Advance(m_StepSize);
                m_CurrentStep = m_MultiStepSequencer.CurrentStep();
                m_CurrentStep.s_IsActive &= m_IsActive;//if not active, do not play the current step

                int CurrentStepIndex = m_MultiStepSequencer.GetCurrentStep();
                m_Callback(CurrentStepIndex);

                if(m_CurrentStep.s_IsActive)
                {
                    // change frequency + trigger on
                    *TriggerOutBuffer = 1.0f;
                    m_Frequency = CMidiNotePitch()(CMidiNoteConverter().ToMidiNote(m_CurrentStep.s_Note, m_CurrentStep.s_Octave));
                    // note: in case long release and non-active step,
                    // must keep the frequency of the previous active step!
                }
            }
            else if(*ClockBuffer<-0.99f)
            {
                // note off previous step
                if(m_CurrentStep.s_IsActive)
                {
                    // trigger off, keep frequency
                    *TriggerOutBuffer = -1.0f;
                    m_CurrentStep.s_IsActive = false;
                }
            }
            *FreqOutBuffer = m_Frequency;

            ++ClockBuffer;
            ++TriggerOutBuffer;
            ++FreqOutBuffer;
        }
    }

    return 0;
}

int CMultiStepSequencerFilter::GetMaxNumSteps() const
{
    return m_MultiStepSequencer.GetMaxNumSteps();
}

void CMultiStepSequencerFilter::SetActive(int Step, bool IsActive)
{
    m_MultiStepSequencer.SetActive(Step, IsActive);
}

void CMultiStepSequencerFilter::SetOctave(int Step, EOctave Octave)
{
    m_MultiStepSequencer.SetOctave(Step, Octave);
}

void CMultiStepSequencerFilter::SetNote(int Step, ENote Note)
{
    m_MultiStepSequencer.SetNote(Step, Note);
}

void CMultiStepSequencerFilter::SetStepSize(int StepSize)
{
    m_StepSize = StepSize;
}

void CMultiStepSequencerFilter::SetActive(bool Active)
{
    m_IsActive = Active;
}

void CMultiStepSequencerFilter::SetNumSteps(int NumSteps)
{
    m_MultiStepSequencer.SetNumSteps(NumSteps);
}
