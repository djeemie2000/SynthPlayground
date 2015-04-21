#include "MultiStepSequencer.h"
#include "Pitch.h"

CMultiStepSequencer::SStep::SStep()
 : s_Velocity(92)
 , s_Note(ENote::A)
 , s_Octave(EOctave::Octave2)
 , s_StepMode(EStepMode::Off)
 , s_NumSubSteps(1)
 , s_SubStepGateMode(ESubStepGateMode::Repeat)
 , s_Duration(64)
{
}


CMultiStepSequencer::CMultiStepSequencer(int N)
 : m_ClockSubDivision(128)
// , m_Pitch()
 , m_Steps(N)
 , m_CurrentStep(0)
 , m_CurrentSubStep(0)
 , m_StepIntervalLength(N)
 , m_StepIntervalBegin(0)
 , m_IntervalStep(0)
 , m_ClockCounter(0)
 , m_Gate(1)
 , m_Frequency(0)
 , m_Velocity(0)
{
    m_Frequency = CPitch()(m_Steps[m_CurrentStep].s_Note, m_Steps[m_CurrentStep].s_Octave);
    m_Velocity = m_Steps[m_CurrentStep].s_Velocity/static_cast<float>(m_ClockSubDivision);
}


int CMultiStepSequencer::GetMaxNumSteps() const
{
    return static_cast<int>(m_Steps.size());
}


void CMultiStepSequencer::SetStepMode(int Step, EStepMode Mode)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_StepMode = Mode;
    }
}


void CMultiStepSequencer::SetVelocity(int Step, int Velocity)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Velocity = Velocity;//TODO check range?
    }
}


void CMultiStepSequencer::SetDuration(int Step, int Duration)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Duration = Duration;//TODO check range?
    }
}


void CMultiStepSequencer::SetNumSubSteps(int Step, int NumSubSteps)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_NumSubSteps = NumSubSteps;//TODO check range?
    }
}


void CMultiStepSequencer::SetSubStepMode(int Step, ESubStepGateMode Mode)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_SubStepGateMode = Mode;
    }
}


void CMultiStepSequencer::SetOctave(int Step, EOctave Octave)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Octave = Octave;
    }
}


void CMultiStepSequencer::SetNote(int Step, ENote Note)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Note = Note;
    }
}


void CMultiStepSequencer::SetStepIntervalBegin(int Step)
{
    if(0<Step && Step<=GetMaxNumSteps())
    {
        m_StepIntervalBegin = Step;
    }
}


void CMultiStepSequencer::SetStepIntervalLength(int Length)
{
    if(0<Length && Length<=GetMaxNumSteps())
    {
        m_StepIntervalLength = Length;
    }
}


void CMultiStepSequencer::SetStepSize(int StepSize)
{
    //TODO
    int bs = StepSize;
}


void CMultiStepSequencer::AdvanceClock()
{
    ++m_ClockCounter;
    if(m_ClockSubDivision<=m_ClockCounter)
    {
        m_ClockCounter = 0;
        ++m_CurrentSubStep;
        if(m_Steps[m_CurrentStep].s_NumSubSteps<=m_CurrentSubStep)
        {
            m_CurrentSubStep = 0;
            AdvanceStep();
            // frequency and velocity only change upon beginning of a new step
            m_Frequency = CPitch()(m_Steps[m_CurrentStep].s_Note, m_Steps[m_CurrentStep].s_Octave);
            m_Velocity = m_Steps[m_CurrentStep].s_Velocity/static_cast<float>(m_ClockSubDivision);
        }
    }
    // gate changes upon clock, depending on gate mode
    if(m_Steps[m_CurrentStep].s_SubStepGateMode == ESubStepGateMode::Repeat)
    {
        m_Gate = m_ClockCounter<m_Steps[m_CurrentStep].s_Duration ? 1 : 0;//gate mode = Repeat
    }
    else if(m_Steps[m_CurrentStep].s_SubStepGateMode == ESubStepGateMode::Single)
    {
        m_Gate = (m_CurrentSubStep==0 && m_ClockCounter<m_Steps[m_CurrentStep].s_Duration) ? 1 : 0;//gate mode = Single
    }
    else if(m_Steps[m_CurrentStep].s_SubStepGateMode == ESubStepGateMode::Length)
    {
        int CurrentLength = m_CurrentSubStep*m_ClockSubDivision + m_ClockCounter;
        int StepLength = m_Steps[m_CurrentStep].s_NumSubSteps * m_ClockSubDivision;
        int GateLength = m_Steps[m_CurrentStep].s_Duration * StepLength / m_ClockSubDivision;
        m_Gate = CurrentLength<GateLength ? 1 : 0;//gate mode = Length
    }
}


bool CMultiStepSequencer::StepExists(int Step) const
{
    return 0<=Step && Step<GetMaxNumSteps();
}


void CMultiStepSequencer::AdvanceStep()
{
    //use actual number of steps instead of the maximum number of steps!
    m_IntervalStep = (m_IntervalStep+1)%m_StepIntervalLength;
    m_CurrentStep = m_StepIntervalBegin+m_IntervalStep;
}
