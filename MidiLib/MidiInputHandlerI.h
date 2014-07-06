#ifndef MIDIINPUTHANDLERI_H
#define MIDIINPUTHANDLERI_H

class IMidiInputHandler
{
public:
    virtual ~IMidiInputHandler(){}

    virtual void OnNoteOn(int Note, int Velocity) =0;
    virtual void OnNoteOff(int Note, int Velocity) =0;
    virtual void OnController(int Parameter, int Value) =0;
    virtual void OnPitchbend(int Value) =0;
    virtual void OnUnknown() =0;
};

#endif // MIDIINPUTHANDLERI_H
