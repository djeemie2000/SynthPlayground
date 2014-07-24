#ifndef STEPSEQUENCERI_H
#define STEPSEQUENCERI_H

#include "Notes.h"

class IStepSequencer
{
public:
    virtual ~IStepSequencer(){}

    virtual int GetMaxNumSteps() const =0;
    virtual void SetActive(int Step, bool IsActive) =0;
    virtual void SetOctave(int Step, EOctave Octave) =0;
    virtual void SetNote(int Step, ENote Note) =0;
    virtual void SetBeatsPerMinute(int Bpm) =0;
    virtual void SetBarsPerBeat(int BarsPerBeat) =0;
    virtual void SetNumSteps(int NumSteps) =0;
    virtual void Start() =0;
    virtual void Stop() =0;

};

#endif // STEPSEQUENCERI_H
