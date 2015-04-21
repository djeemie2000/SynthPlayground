#pragma once

#include "Notes.h"

class CPitch
{
public:
    CPitch();

    float operator()(ENote Note, EOctave Octave);
};
