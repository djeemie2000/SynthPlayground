#ifndef STEPSEQUENCER_H
#define STEPSEQUENCER_H

#include <vector>
#include "Notes.h"
#include <memory>

class CController;
template<class T> class CPeriodicThreadRunner;

class CStepSequencer
{
public:
    CStepSequencer(int NumSteps, CController& NoteHandler);
    ~CStepSequencer();

    int NumSteps() const;

    void SetActive(int Step, bool IsActive);
    void SetOctave(int Step, EOctave Octave);
    void SetNote(int Step, ENote Note);

    void SetBeatsPerMinute(int Bpm);
    void SetBarsPerBeat(int BarsPerBeat);

    void Start();
    void Stop();

    void OnTick();

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
    int PeriodMilliSeconds() const;

    CController& m_NoteHandler;

    std::vector<SStep> m_Steps;
    int m_CurrentStep;

    SStep m_PreviousStep;

    int m_Bpm;
    int m_BarsPerBeat;
    std::unique_ptr<CPeriodicThreadRunner<CStepSequencer>> m_ThreadRunner;
};

#endif // STEPSEQUENCER_H
