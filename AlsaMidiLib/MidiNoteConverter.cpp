#include "MidiNoteConverter.h"

CMidiNoteConverter::CMidiNoteConverter()
{
}

namespace
{

ENote NoteTable[] =
{
    // octave -1
    ENote::C,
    ENote::Csharp,
    ENote::D,
    ENote::Dsharp,
    ENote::E,
    ENote::F,
    ENote::Fsharp,
    ENote::G,
    ENote::Gsharp,
    ENote::A,
    ENote::Asharp,
    ENote::B,
    // octave 0
    ENote::C,
    ENote::Csharp,
    ENote::D,
    ENote::Dsharp,
    ENote::E,
    ENote::F,
    ENote::Fsharp,
    ENote::G,
    ENote::Gsharp,
    ENote::A,
    ENote::Asharp,
    ENote::B,
    // octave 1
    ENote::C,
    ENote::Csharp,
    ENote::D,
    ENote::Dsharp,
    ENote::E,
    ENote::F,
    ENote::Fsharp,
    ENote::G,
    ENote::Gsharp,
    ENote::A,
    ENote::Asharp,
    ENote::B,
    // octave 2
    ENote::C,
    ENote::Csharp,
    ENote::D,
    ENote::Dsharp,
    ENote::E,
    ENote::F,
    ENote::Fsharp,
    ENote::G,
    ENote::Gsharp,
    ENote::A,
    ENote::Asharp,
    ENote::B,
    // octave 3
    ENote::C,
    ENote::Csharp,
    ENote::D,
    ENote::Dsharp,
    ENote::E,
    ENote::F,
    ENote::Fsharp,
    ENote::G,
    ENote::Gsharp,
    ENote::A,
    ENote::Asharp,
    ENote::B,
    // octave 4
    ENote::C,
    ENote::Csharp,
    ENote::D,
    ENote::Dsharp,
    ENote::E,
    ENote::F,
    ENote::Fsharp,
    ENote::G,
    ENote::Gsharp,
    ENote::A,
    ENote::Asharp,
    ENote::B,
    // octave 5
    ENote::C,
    ENote::Csharp,
    ENote::D,
    ENote::Dsharp,
    ENote::E,
    ENote::F,
    ENote::Fsharp,
    ENote::G,
    ENote::Gsharp,
    ENote::A,
    ENote::Asharp,
    ENote::B,
    // octave 6
    ENote::C,
    ENote::Csharp,
    ENote::D,
    ENote::Dsharp,
    ENote::E,
    ENote::F,
    ENote::Fsharp,
    ENote::G,
    ENote::Gsharp,
    ENote::A,
    ENote::Asharp,
    ENote::B,
    // octave 7
    ENote::C,
    ENote::Csharp,
    ENote::D,
    ENote::Dsharp,
    ENote::E,
    ENote::F,
    ENote::Fsharp,
    ENote::G,
    ENote::Gsharp,
    ENote::A,
    ENote::Asharp,
    ENote::B,
    // octave 8
    ENote::C,
    ENote::Csharp,
    ENote::D,
    ENote::Dsharp,
    ENote::E,
    ENote::F,
    ENote::Fsharp,
    ENote::G,
    ENote::Gsharp,
    ENote::A,
    ENote::Asharp,
    ENote::B,
    // octave 9??
    ENote::C,
    ENote::Csharp,
    ENote::D,
    ENote::Dsharp,
    ENote::E,
    ENote::F,
    ENote::Fsharp,
    ENote::G,
    ENote::Gsharp,
    ENote::A,
    ENote::Asharp,
    ENote::B
};

}

ENote CMidiNoteConverter::ToNote(int MidiNote)
{
    // assume MidiNote in [0, 9*12[
    return NoteTable[MidiNote];
    // alternative:  static_cast<ENote>(returnMidiNote % NumNotesPerOctave);

}

namespace
{

EOctave OctaveTable[] =
{
    // octave -1
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    // octave 0
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    EOctave::Octave0,
    // octave 1
    EOctave::Octave1,
    EOctave::Octave1,
    EOctave::Octave1,
    EOctave::Octave1,
    EOctave::Octave1,
    EOctave::Octave1,
    EOctave::Octave1,
    EOctave::Octave1,
    EOctave::Octave1,
    EOctave::Octave1,
    EOctave::Octave1,
    EOctave::Octave1,
    // octave 2
    EOctave::Octave2,
    EOctave::Octave2,
    EOctave::Octave2,
    EOctave::Octave2,
    EOctave::Octave2,
    EOctave::Octave2,
    EOctave::Octave2,
    EOctave::Octave2,
    EOctave::Octave2,
    EOctave::Octave2,
    EOctave::Octave2,
    EOctave::Octave2,
    // octave 3
    EOctave::Octave3,
    EOctave::Octave3,
    EOctave::Octave3,
    EOctave::Octave3,
    EOctave::Octave3,
    EOctave::Octave3,
    EOctave::Octave3,
    EOctave::Octave3,
    EOctave::Octave3,
    EOctave::Octave3,
    EOctave::Octave3,
    // octave 4
    EOctave::Octave4,
    EOctave::Octave4,
    EOctave::Octave4,
    EOctave::Octave4,
    EOctave::Octave4,
    EOctave::Octave4,
    EOctave::Octave4,
    EOctave::Octave4,
    EOctave::Octave4,
    EOctave::Octave4,
    EOctave::Octave4,
    // octave 5
    EOctave::Octave5,
    EOctave::Octave5,
    EOctave::Octave5,
    EOctave::Octave5,
    EOctave::Octave5,
    EOctave::Octave5,
    EOctave::Octave5,
    EOctave::Octave5,
    EOctave::Octave5,
    EOctave::Octave5,
    EOctave::Octave5,
    // octave 6
    EOctave::Octave6,
    EOctave::Octave6,
    EOctave::Octave6,
    EOctave::Octave6,
    EOctave::Octave6,
    EOctave::Octave6,
    EOctave::Octave6,
    EOctave::Octave6,
    EOctave::Octave6,
    EOctave::Octave6,
    EOctave::Octave6,
    // octave 7
    EOctave::Octave7,
    EOctave::Octave7,
    EOctave::Octave7,
    EOctave::Octave7,
    EOctave::Octave7,
    EOctave::Octave7,
    EOctave::Octave7,
    EOctave::Octave7,
    EOctave::Octave7,
    EOctave::Octave7,
    EOctave::Octave7,
    // octave 8
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    // octave 9?
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8,
    EOctave::Octave8
};

}

EOctave CMidiNoteConverter::ToOctave(int MidiNote)
{
    // assume MidiNote in [0, 9*12[
    return OctaveTable[MidiNote];
    // alternative : return static_cast<EOctave>(-1 + MidiNote/NumNotesPerOctave);
}

namespace
{

const int NumNotesPerOctave = 12;

}

int CMidiNoteConverter::ToMidiNote(ENote Note, EOctave Octave)
{
    return NumNotesPerOctave*(1+static_cast<int>(Octave)) + static_cast<int>(Note);
}
