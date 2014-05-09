#ifndef PITCH_H
#define PITCH_H

#include "Notes.h"

class CPitch
{
public:
    CPitch();

    float operator()(ENote Note, EOctave Octave);
};

#endif // PITCH_H
