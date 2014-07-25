#include "StepSequencerController.h"
#include "MidiNoteConverter.h"
#include "MidiInputHandlerI.h"

CStepSequencerController::CStepSequencerController(int SamplingFrequency, std::shared_ptr<IMidiInputHandler> MidiInputHandler, std::shared_ptr<IMidiSource> MidiSource)
    : m_MidiInputHandler(MidiInputHandler)
    , m_MidiSource(MidiSource)
    , m_StepSequencer(SamplingFrequency)
    , m_CurrentStep()
    , m_IsActive(false)
    , m_Counter(0)
{
    m_StepSequencer.SetBeatsPerMinute(120);
    m_StepSequencer.SetBarsPerBeat(2);
}

int CStepSequencerController::GetMaxNumSteps() const
{
    return m_StepSequencer.GetMaxNumSteps();
}

void CStepSequencerController::SetActive(int Step, bool IsActive)
{
    m_StepSequencer.SetActive(Step, IsActive);
}

void CStepSequencerController::SetOctave(int Step, EOctave Octave)
{
    m_StepSequencer.SetOctave(Step, Octave);
}

void CStepSequencerController::SetNote(int Step, ENote Note)
{
    m_StepSequencer.SetNote(Step, Note);
}

void CStepSequencerController::SetBeatsPerMinute(int Bpm)
{
    m_StepSequencer.SetBeatsPerMinute(Bpm);
}

void CStepSequencerController::SetBarsPerBeat(int BarsPerBeat)
{
    m_StepSequencer.SetBarsPerBeat(BarsPerBeat);
}

void CStepSequencerController::SetNumSteps(int NumSteps)
{
    m_StepSequencer.SetNumSteps(NumSteps);
}

void CStepSequencerController::Start()
{
    //std::printf"StepSequencer Start \r\n");
    m_IsActive = true;
}

void CStepSequencerController::Stop()
{
    //std::printf"StepSequencer Stop \r\n");
    m_IsActive = false;
}

void CStepSequencerController::SetDuration(int DurationPercentage)
{
    m_StepSequencer.SetDuration(DurationPercentage);
}

int CStepSequencerController::OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp)
{
    int Frame = 0;
    while(Frame<NumFrames)
    {
        const int MidiNoteVelocity = 127;

        if(m_Counter==0)//m_StepSequencerTicker())
        {
            // note off previous step, advance to next step, apply!
            if(m_CurrentStep.s_IsActive)
            {
                int MidiNote = CMidiNoteConverter().ToMidiNote(m_CurrentStep.s_Note, m_CurrentStep.s_Octave);
                m_MidiInputHandler->OnNoteOff(MidiNote, MidiNoteVelocity, Frame);
            }

            m_StepSequencer.Advance();
            m_CurrentStep = m_StepSequencer.CurrentStep();
            m_CurrentStep.s_IsActive &= m_IsActive;//if not active, do not play the current step

            if(m_CurrentStep.s_IsActive)
            {
                int MidiNote = CMidiNoteConverter().ToMidiNote(m_CurrentStep.s_Note, m_CurrentStep.s_Octave);
                m_MidiInputHandler->OnNoteOn(MidiNote, MidiNoteVelocity, Frame);
            }
        }
        else if(m_Counter==m_StepSequencer.DurationSamples())
        {
            // note off previous step
            if(m_CurrentStep.s_IsActive)
            {
                int MidiNote = CMidiNoteConverter().ToMidiNote(m_CurrentStep.s_Note, m_CurrentStep.s_Octave);
                m_MidiInputHandler->OnNoteOff(MidiNote, MidiNoteVelocity, Frame);
                m_CurrentStep.s_IsActive = false;
            }
        }

        ++m_Counter;
        if(m_StepSequencer.PeriodSamples()<=m_Counter)
        {
            m_Counter = 0;
        }

        ++Frame;
    }

    m_MidiSource->OnRead(Dst, NumFrames, TimeStamp);

    return 0; // zero means ok
}
