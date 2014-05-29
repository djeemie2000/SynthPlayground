#include "StepSequencer.h"
#include "NoteHandlerI.h"
#include "PeriodicThreadRunner.h"

CStepSequencer::CStepSequencer(int NumSteps, INoteHandler &NoteHandler)
    : m_NoteHandler(NoteHandler)
    , m_Steps(NumSteps)
    , m_CurrentStep(0)
    , m_Bpm(120)
    , m_BarsPerBeat(2)
    , m_ThreadRunner()
{
    m_ThreadRunner.reset(new CPeriodicThreadRunner<CStepSequencer>(*this));
    m_ThreadRunner->SetPeriod(PeriodMilliSeconds());
}

CStepSequencer::~CStepSequencer()
{
}

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

void CStepSequencer::SetBeatsPerMinute(int Bpm)
{
    m_Bpm = Bpm;
    m_ThreadRunner->SetPeriod(PeriodMilliSeconds());
}

void CStepSequencer::SetBarsPerBeat(int BarsPerBeat)
{
    m_BarsPerBeat = BarsPerBeat;
    m_ThreadRunner->SetPeriod(PeriodMilliSeconds());
}

void CStepSequencer::Start()
{
    m_ThreadRunner->Start();
}

void CStepSequencer::Stop()
{
    m_ThreadRunner->Stop();
}

void CStepSequencer::OnTick()
{
    // noteOff, use dedicated member in case step is changed since previous OnTick()
    m_PreviousStep.NoteOff(m_NoteHandler);

    // noteOn, see above remarks
    m_PreviousStep = m_Steps[m_CurrentStep];
    m_PreviousStep.NoteOn(m_NoteHandler);

    // to next step
    m_CurrentStep = (m_CurrentStep+1)%NumSteps();
}

int CStepSequencer::NumSteps() const
{
    return static_cast<int>(m_Steps.size());
}

bool CStepSequencer::StepExists(int Step) const
{
    return 0<=Step && Step<NumSteps();
}

int CStepSequencer::PeriodMilliSeconds() const
{
    return 60 * 1000 / (m_Bpm * m_BarsPerBeat);
}

CStepSequencer::SStep::SStep()
 : s_IsActive(false)
 , s_Note(ENote::A)
 , s_Octave(EOctave::Octave2)
{
}

void CStepSequencer::SStep::NoteOn(INoteHandler &NoteHandler)
{
    if(s_IsActive)
    {
        NoteHandler.OnNoteOn(s_Note, s_Octave);
    }
}

void CStepSequencer::SStep::NoteOff(INoteHandler &NoteHandler)
{
    if(s_IsActive)
    {
        NoteHandler.OnNoteOff(s_Note, s_Octave);
    }
}
