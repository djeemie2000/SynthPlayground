#pragma once

#include <vector>
#include "Notes.h"

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

    CMultiStepSequencer(int N);

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

    float GetGate() const   {   return m_Gate;  }
    float GetFrequency() const  {   return m_Frequency;  }
    float GetVelocity() const   {   return m_Velocity;  }
    // GetMidiNote(), GetNote(), GetOctave() can be implemented similar to above
    // Trigger = curr Gate - prev Gate

    // feedback to gui
    int GetMaxNumSteps() const;
    int GetCurrentStep() const { return m_CurrentStep; }
    int GetCurrentSubStep() const   {   return m_CurrentSubStep;    }

private:
    bool StepExists(int Step) const;
    void AdvanceStep();//?????

    const int m_ClockSubDivision;

    std::vector<SStep> m_Steps;
    int m_CurrentStep;
    int m_CurrentSubStep;
    int m_StepIntervalLength;
    int m_StepIntervalBegin;
    int m_IntervalStep;

    int m_ClockCounter;

    float m_Gate;
    float m_Frequency;
    float m_Velocity;
};
