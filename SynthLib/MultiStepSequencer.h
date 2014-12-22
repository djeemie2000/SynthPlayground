#ifndef MULTISTEPSEQUENCER_H
#define MULTISTEPSEQUENCER_H

#include <array>
#include "Notes.h"
#include "Pitch.h"

template<class T, int N>
class CMultiStepSequencer
{
public:
    enum class EStepMode : int
    {
        Off =0,
        On =1,
        Skip =2
    };

    enum class ESubStepGateMode : int
    {
        Repeat = 0,
        Single = 1,
        Length = 2
    };

    struct SStep
    {
        int     s_Velocity;//[0,127]
        ENote   s_Note;
        EOctave s_Octave;
        EStepMode s_StepMode;
        int     s_NumSubSteps;// repeat/length ?? rename?
        ESubStepGateMode s_SubStepGateMode;
        int     s_Duration; //[0,127]
        SStep();
    };

    CMultiStepSequencer();

    // step settings:
    void SetNote(int Step, ENote Note);
    void SetOctave(int Step, EOctave Octave);
    void SetStepMode(int Step, EStepMode Mode);
    void SetVelocity(int Step, int Velocity);
    void SetDuration(int Step, int Duration);
    void SetNumSubSteps(int Step, int NumSubSteps);
    void SetSubStepMode(int Step, ESubStepGateMode Mode);

    // step interval settings:
    void SetStepIntervalBegin(int Step);
    void SetStepIntervalLength(int Length);
    void SetStepSize(int StepSize);// advance 1, 2, 3, ... steps

    void AdvanceClock();//TODO???? return action: new note on (which freq/velocity???)/current note off/do nothing
    // GetFrequency(), GetVelocity(), GetGate(), GetTrigger()??, GetMidiNote(), GetNote(), GetOctave()??

    // feedback to gui
    int GetMaxNumSteps() const;
    int GetCurrentStep() const { return m_CurrentStep; }
    int GetCurrentSubStep() const   {   return m_CurrentSubStep;    }

private:
    bool StepExists(int Step) const;
    void AdvanceStep();//?????

    const int m_ClockSubDivision;
    std::array<SStep, N> m_Steps;
    int m_CurrentStep;
    int m_CurrentSubStep;
    int m_StepIntervalLength;
    int m_StepIntervalBegin;
    int m_IntervalStep;
};

template<class T, int N>
CMultiStepSequencer<T,N>::SStep::SStep()
 : s_Velocity(92)
 , s_Note(ENote::A)
 , s_Octave(EOctave::Octave2)
 , s_StepMode(EStepMode::Off)
 , s_NumSubSteps(1)
 , s_SubStepGateMode(ESubStepGateMode::Repeat)
 , s_Duration(64)
{
}

template<class T, int N>
CMultiStepSequencer<T,N>::CMultiStepSequencer()
 : m_ClockSubDivision(128)
 , m_Steps()
 , m_CurrentStep(0)
 , m_CurrentSubStep(0)
 , m_StepIntervalLength(N)
 , m_StepIntervalBegin(0)
 , m_IntervalStep(0)
 {
    m_Steps.fill(SStep());
}

template<class T, int N>
int CMultiStepSequencer<T,N>::GetMaxNumSteps() const
{
    return N;
}

//template<class T, int N>
//void CMultiStepSequencer<T,N>::SetActive(int Step, bool IsActive)
//{
//    if(StepExists(Step))
//    {
//        m_Steps[Step].s_IsActive = IsActive;
//    }
//}

template<class T, int N>
void CMultiStepSequencer<T,N>::SetStepMode(int Step, EStepMode Mode)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_StepMode = Mode;
    }
}

template<class T, int N>
void CMultiStepSequencer<T,N>::SetVelocity(int Step, int Velocity)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Velocity = Velocity;//TODO check range?
    }
}

template<class T, int N>
void CMultiStepSequencer<T,N>::SetDuration(int Step, int Duration)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Duration = Duration;//TODO check range?
    }
}

template<class T, int N>
void CMultiStepSequencer<T,N>::SetNumSubSteps(int Step, int NumSubSteps)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_NumSubSteps = NumSubSteps;//TODO check range?
    }
}

template<class T, int N>
void CMultiStepSequencer<T,N>::SetSubStepMode(int Step, ESubStepGateMode Mode)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_SubStepGateMode = Mode;
    }
}

template<class T, int N>
void CMultiStepSequencer<T,N>::SetOctave(int Step, EOctave Octave)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Octave = Octave;
    }
}

template<class T, int N>
void CMultiStepSequencer<T,N>::SetNote(int Step, ENote Note)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Note = Note;
    }
}

template<class T, int N>
void CMultiStepSequencer<T,N>::SetStepIntervalBegin(int Step)
{
    if(0<Step && Step<=GetMaxNumSteps())
    {
        m_StepIntervalBegin = Step;
    }
}

template<class T, int N>
void CMultiStepSequencer<T,N>::SetStepIntervalLength(int Length)
{
    if(0<Length && Length<=GetMaxNumSteps())
    {
        m_StepIntervalLength = Length;
    }
}

template<class T, int N>
void CMultiStepSequencer<T,N>::AdvanceClock()
{
    //adv clock cntr
    // => note off in substep? => gate off?
    // advance to next substep?
    // advance to next step?
}

template<class T, int N>
bool CMultiStepSequencer<T,N>::StepExists(int Step) const
{
    return 0<=Step && Step<N;
}

template<class T, int N>
void CMultiStepSequencer<T,N>::AdvanceStep()
{
    //use actual number of steps instead of the maximum number of steps!
    m_IntervalStep = (m_IntervalStep+1)%m_StepIntervalLength;
    m_CurrentStep = m_StepIntervalBegin+m_IntervalStep;
}

#endif // MULTISTEPSEQUENCER_H
