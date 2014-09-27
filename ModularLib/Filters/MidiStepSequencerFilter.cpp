#include <algorithm>
#include "MidiStepSequencerFilter.h"
#include "MidiInputHandlerI.h"
#include "MidiNoteConverter.h"

CMidiStepSequencerFilter::CMidiStepSequencerFilter(int SamplingFrequency)
    : m_StepSequencer(SamplingFrequency)
    , m_CurrentStep()
    , m_IsActive(false)
    , m_StepSize(1)
{
}

std::vector<std::string> CMidiStepSequencerFilter::GetInputNames() const
{
    return {"Trigger"};
}

std::vector<std::string> CMidiStepSequencerFilter::GetOutputNames() const
{
    return {};
}

std::vector<std::string> CMidiStepSequencerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CMidiStepSequencerFilter::GetMidiOutputNames() const
{
    return {"MidiOut"};
}

int CMidiStepSequencerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                   const std::vector<void *> &/*DestinationBuffers*/,
                                   const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                   const std::vector<std::shared_ptr<IMidiHandler> > MidiHandlers,
                                   int NumFrames,
                                   std::uint32_t /*TimeStamp*/)
{
    const float* TriggerBuffer = (const float*)(SourceBuffers[0]);
    if(TriggerBuffer && MidiHandlers[0])
    {
        const int MidiNoteVelocity = 127;

        int Frame = 0;
        const float* TriggerBufferEnd = TriggerBuffer + NumFrames;
        while(TriggerBuffer<TriggerBufferEnd)
        {
            if(0.99f<*TriggerBuffer)
            {
                m_StepSequencer.Advance(m_StepSize);
                m_CurrentStep = m_StepSequencer.CurrentStep();
                m_CurrentStep.s_IsActive &= m_IsActive;//if not active, do not play the current step

                if(m_CurrentStep.s_IsActive)
                {
                    int MidiNote = CMidiNoteConverter().ToMidiNote(m_CurrentStep.s_Note, m_CurrentStep.s_Octave);
                    MidiHandlers[0]->OnNoteOn(MidiNote, MidiNoteVelocity, Frame);
                }
            }
            else if(*TriggerBuffer<-0.99f)
            {
                // note off previous step
                if(m_CurrentStep.s_IsActive)
                {
                    int MidiNote = CMidiNoteConverter().ToMidiNote(m_CurrentStep.s_Note, m_CurrentStep.s_Octave);
                    MidiHandlers[0]->OnNoteOff(MidiNote, MidiNoteVelocity, Frame);
                    m_CurrentStep.s_IsActive = false;
                }
            }
            ++TriggerBuffer;
            ++Frame;
        }
    }

    return 0;
}

int CMidiStepSequencerFilter::GetMaxNumSteps() const
{
    return m_StepSequencer.GetMaxNumSteps();
}

void CMidiStepSequencerFilter::SetActive(int Step, bool IsActive)
{
    m_StepSequencer.SetActive(Step, IsActive);
}

void CMidiStepSequencerFilter::SetOctave(int Step, EOctave Octave)
{
    m_StepSequencer.SetOctave(Step, Octave);
}

void CMidiStepSequencerFilter::SetNote(int Step, ENote Note)
{
    m_StepSequencer.SetNote(Step, Note);
}

void CMidiStepSequencerFilter::SetStepSize(int StepSize)
{
    m_StepSize = StepSize;
}

void CMidiStepSequencerFilter::SetActive(bool Active)
{
    m_IsActive = Active;
}

void CMidiStepSequencerFilter::SetNumSteps(int NumSteps)
{
    m_StepSequencer.SetNumSteps(NumSteps);
}
