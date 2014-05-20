#include "Notes.h"

std::string ToString(ENote /*Note*/)
{
    return "AAAAA";
}

ENote FromString(const std::string& Note)
{
    if(Note=="B")
    {
        return ENote::B;
    }
    if(Note=="A#")
    {
        return ENote::Asharp;
    }
    if(Note=="A")
    {
        return ENote::A;
    }
    if(Note=="G#")
    {
        return ENote::Gsharp;
    }
    if(Note=="G")
    {
        return ENote::G;
    }
    if(Note=="F#")
    {
        return ENote::Fsharp;
    }
    if(Note=="F")
    {
        return ENote::F;
    }
    if(Note=="E")
    {
        return ENote::E;
    }
    if(Note=="D#")
    {
        return ENote::Dsharp;
    }
    if(Note=="D")
    {
        return ENote::D;
    }
    if(Note=="C#")
    {
        return ENote::Csharp;
    }
    if(Note=="C")
    {
        return ENote::C;
    }

    return ENote::A;
}

//std::vector<std::string> CreateNoteList()
//{
//    //return { "B", "A#", "A", "G#", "G", "F#", "F", "E", "D#", "D", "C#", "C" };
//    return { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
//}


std::vector<std::string> CNoteList::Create()
{
    //return { "B", "A#", "A", "G#", "G", "F#", "F", "E", "D#", "D", "C#", "C" };
    return { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
}
