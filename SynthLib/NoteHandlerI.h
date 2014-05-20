#ifndef NOTEHANDLERI_H
#define NOTEHANDLERI_H

#include "Notes.h"

class INoteHandler
{
public:
    virtual ~INoteHandler(){}

    virtual void OnNoteOn(ENote Note, EOctave Octave) =0;
    virtual void OnNoteOff(ENote Note, EOctave Octave) =0;
};

#endif // NOTEHANDLERI_H
