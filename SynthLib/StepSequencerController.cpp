#include "StepSequencerController.h"
#include "MidiNoteConverter.h"
#include "MidiInputHandlerI.h"

CStepSequencerController::CStepSequencerController(int SamplingFrequency, std::shared_ptr<IMidiInputHandler> MidiInputHandler, std::shared_ptr<IMidiSource> MidiSource)
    : m_MidiInputHandler(MidiInputHandler)
    , m_MidiSource(MidiSource)
    , m_StepSequencer(SamplingFrequency)
    , m_CurrentStep()
    , m_StepSequencerTicker()
    , m_IsActive(false)
{
    m_StepSequencer.SetBeatsPerMinute(120);
    m_StepSequencer.SetBarsPerBeat(2);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
    m_StepSequencerTicker.Activate(true);//always active!
}

int CStepSequencerController::NumSteps() const
{
    return m_StepSequencer.NumSteps();
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
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

void CStepSequencerController::SetBarsPerBeat(int BarsPerBeat)
{
    m_StepSequencer.SetBarsPerBeat(BarsPerBeat);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
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

int CStepSequencerController::OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp)
{
    int Frame = 0;
    while(Frame<NumFrames)
    {
        if(m_StepSequencerTicker())
        {
            // note off previous step, advance to next step and apply!
            if(m_CurrentStep.s_IsActive)
            {
                int MidiNote = CMidiNoteConverter().ToMidiNote(m_CurrentStep.s_Note, m_CurrentStep.s_Octave);
                m_MidiInputHandler->OnNoteOff(MidiNote, 127, Frame);
            }

            m_StepSequencer.Advance();
            m_CurrentStep = m_StepSequencer.CurrentStep();
            m_CurrentStep.s_IsActive &= m_IsActive;//if not active, do not play the current step

            if(m_CurrentStep.s_IsActive)
            {
                int MidiNote = CMidiNoteConverter().ToMidiNote(m_CurrentStep.s_Note, m_CurrentStep.s_Octave);
                m_MidiInputHandler->OnNoteOn(MidiNote, 127, Frame);
            }
        }
        ++Frame;
    }

    m_MidiSource->OnRead(Dst, NumFrames, TimeStamp);

    return 0; // zero means ok
}
