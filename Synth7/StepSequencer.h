#ifndef STEPSEQUENCER_H
#define STEPSEQUENCER_H

#include <vector>
#include "Notes.h"

class CController;

class CStepSequencer
{
public:
    CStepSequencer(int NumSteps)
        : m_Active(false)
        , m_Steps(NumSteps)
        , m_CurrentStep(0)
    {}

    int NumSteps() const;

    void SetActive(int Step, bool IsActive);
    void SetOctave(int Step, EOctave Octave);
    void SetNote(int Step, ENote Note);

    void OnActive(bool Active);
    void OnTick(CController& NoteHandler);

private:
    struct SStep
    {
        bool s_IsActive;
        ENote   s_Note;
        EOctave s_Octave;

        SStep();

        void NoteOn(CController& NoteHandler);
        void NoteOff(CController& NoteHandler);
    };

    bool StepExists(int Step) const;

    bool m_Active;
    std::vector<SStep> m_Steps;
    int m_CurrentStep;
    SStep m_PreviousStep;
};

#endif // STEPSEQUENCER_H
