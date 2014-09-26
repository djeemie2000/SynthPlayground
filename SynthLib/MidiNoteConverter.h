#ifndef MIDINOTECONVERTER_H
#define MIDINOTECONVERTER_H

#include "Notes.h"

class CMidiNoteConverter
{
public:
    CMidiNoteConverter() {}

    ENote ToNote(int MidiNote);
    EOctave ToOctave(int MidiNote);
    int ToMidiNote(ENote Note, EOctave Octave)
    {
        return NumNotesPerOctave*(1+static_cast<int>(Octave)) + static_cast<int>(Note);
    }

private:
    static const int NumNotesPerOctave = 12;
};

#endif // MIDINOTECONVERTER_H
