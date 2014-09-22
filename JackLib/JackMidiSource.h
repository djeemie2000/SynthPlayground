#ifndef JACKMIDISOURCE_H
#define JACKMIDISOURCE_H

#include <vector>
#include "MidiSourceI.h"
#include "MidiInputHandlerI.h"
#include <jack/ringbuffer.h>

class CJackMidiSource : public IMidiSource,
                        public IMidiHandler
{
public:
    CJackMidiSource();
    ~CJackMidiSource();

    int OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp) override;

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

private:
    jack_ringbuffer_t* m_RingBuffer;
    std::vector<unsigned char> m_IntermediateBuffer;
};

#endif // JACKMIDISOURCE_H
