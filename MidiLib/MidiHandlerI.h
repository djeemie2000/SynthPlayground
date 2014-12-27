#ifndef MIDIINPUTHANDLERI_H
#define MIDIINPUTHANDLERI_H

#include <cstdint>

class IMidiHandler
{
public:
    virtual ~IMidiHandler(){}

    virtual void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) =0;
    virtual void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) =0;
    virtual void OnController(int Parameter, int Value, std::uint32_t TimeStamp) =0;
    virtual void OnPitchbend(int Value, std::uint32_t TimeStamp) =0;
    virtual void OnUnknown(std::uint32_t TimeStamp) =0;
};

#endif // MIDIINPUTHANDLERI_H
