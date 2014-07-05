#ifndef MIDINOTECONVERTER_H
#define MIDINOTECONVERTER_H

#include "Notes.h"

class CMidiNoteConverter
{
public:
    CMidiNoteConverter();

    ENote ToNote(int MidiNote);
    EOctave ToOctave(int MidiNote);
    int ToMidiNote(ENote Note, EOctave Octave);
};

#endif // MIDINOTECONVERTER_H
