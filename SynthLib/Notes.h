#ifndef NOTES_H
#define NOTES_H

#include <string>
#include <vector>

enum class ENote : int
{
    C = 0,
    Csharp,
    D,
    Dsharp,
    E,
    F,
    Fsharp,
    G,
    Gsharp,
    A,
    Asharp,
    B
};

std::string ToString(ENote Note);
ENote FromString(const std::string& Note);
std::vector<std::string> NoteList();


enum class EOctave : int
{
    Octave0  = 0,
    Octave1,
    Octave2,
    Octave3,
    Octave4,
    Octave5,
    Octave6,
    Octave7,
    Octave8
};

#endif // NOTES_H
