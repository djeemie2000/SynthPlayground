#include "StepSequencer.h"

#include "Controller.h"

void CStepSequencer::SetActive(int Step, bool IsActive)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_IsActive = IsActive;
    }
}

void CStepSequencer::SetOctave(int Step, EOctave Octave)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Octave = Octave;
    }
}

void CStepSequencer::SetNote(int Step, ENote Note)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Note = Note;
    }
}

void CStepSequencer::OnActive(bool Active)
{
    m_Active = Active;
}

void CStepSequencer::OnTick(CController &NoteHandler)
{
    // noteOff, use dedicated member in case step is changed since previous OnTick()
    m_PreviousStep.NoteOff(NoteHandler);

    if(m_Active)
    {
        // noteOn, see above remarks
        m_PreviousStep = m_Steps[m_CurrentStep];
        m_PreviousStep.NoteOn(NoteHandler);

        // to next step
        m_CurrentStep = (m_CurrentStep+1)%NumSteps();
    }
}

int CStepSequencer::NumSteps() const
{
    return static_cast<int>(m_Steps.size());
}

bool CStepSequencer::StepExists(int Step) const
{
    return 0<=Step && Step<NumSteps();
}

CStepSequencer::SStep::SStep()
 : s_IsActive(false)
 , s_Note(ENote::A)
 , s_Octave(EOctave::Octave2)
{
}

void CStepSequencer::SStep::NoteOn(CController &NoteHandler)
{
    if(s_IsActive)
    {
        NoteHandler.OnNoteOn(s_Note, s_Octave);
    }
}

void CStepSequencer::SStep::NoteOff(CController &NoteHandler)
{
    if(s_IsActive)
    {
        NoteHandler.OnNoteOff(s_Note, s_Octave);
    }
}
