#include <algorithm>
#include "StepSequencerFilter.h"
#include "MidiNotePitch.h"
#include "MidiNoteConverter.h"

CStepSequencerFilter::CStepSequencerFilter(int SamplingFrequency, CurrentStepCallbackType Callback)
    : m_StepSequencer(SamplingFrequency)
    , m_CurrentStep()
    , m_IsActive(false)
    , m_StepSize(1)
    , m_Frequency(440.0f)
    , m_Callback(Callback)
{
}

std::vector<std::string> CStepSequencerFilter::GetInputNames() const
{
    return {"TriggerIn"};
}

std::vector<std::string> CStepSequencerFilter::GetOutputNames() const
{
    return {"Freq", "TriggerOut"};
}

std::vector<std::string> CStepSequencerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CStepSequencerFilter::GetMidiOutputNames() const
{
    return {};
}

int CStepSequencerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                   const std::vector<void *> &DestinationBuffers,
                                   const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                   const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                   int NumFrames,
                                   std::uint32_t /*TimeStamp*/)
{
    const float* TriggerInBuffer = (const float*)(SourceBuffers[0]);
    float* FreqOutBuffer = (float*)(DestinationBuffers[0]);
    float* TriggerOutBuffer = (float*)(DestinationBuffers[1]);

    if(TriggerInBuffer && TriggerOutBuffer && FreqOutBuffer)
    {
        const float* TriggerInBufferEnd = TriggerInBuffer + NumFrames;
        while(TriggerInBuffer<TriggerInBufferEnd)
        {
            *TriggerOutBuffer = 0.0f;
            if(0.99f<*TriggerInBuffer)
            {
                m_StepSequencer.Advance(m_StepSize);
                m_CurrentStep = m_StepSequencer.CurrentStep();
                m_CurrentStep.s_IsActive &= m_IsActive;//if not active, do not play the current step

                int CurrentStepIndex = m_StepSequencer.GetCurrentStep();
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
            else if(*TriggerInBuffer<-0.99f)
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

            ++TriggerInBuffer;
            ++TriggerOutBuffer;
            ++FreqOutBuffer;
        }
    }

    return 0;
}

int CStepSequencerFilter::GetMaxNumSteps() const
{
    return m_StepSequencer.GetMaxNumSteps();
}

void CStepSequencerFilter::SetActive(int Step, bool IsActive)
{
    m_StepSequencer.SetActive(Step, IsActive);
}

void CStepSequencerFilter::SetOctave(int Step, EOctave Octave)
{
    m_StepSequencer.SetOctave(Step, Octave);
}

void CStepSequencerFilter::SetNote(int Step, ENote Note)
{
    m_StepSequencer.SetNote(Step, Note);
}

void CStepSequencerFilter::SetStepSize(int StepSize)
{
    m_StepSize = StepSize;
}

void CStepSequencerFilter::SetActive(bool Active)
{
    m_IsActive = Active;
}

void CStepSequencerFilter::SetNumSteps(int NumSteps)
{
    m_StepSequencer.SetNumSteps(NumSteps);
}
