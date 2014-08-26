#ifndef MIDINOTEPITCH_H
#define MIDINOTEPITCH_H

class CMidiNotePitch
{
public:
    CMidiNotePitch();

    float operator()(int MidiNote);
};

#endif // MIDINOTEPITCH_H
