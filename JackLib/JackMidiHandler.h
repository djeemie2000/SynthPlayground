#ifndef JACKMIDIHANDLER_H
#define JACKMIDIHANDLER_H

#include "MidiHandlerI.h"

class CJackMidiHandler : public IMidiHandler
{
public:
    CJackMidiHandler(void* DstBuffer);

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

private:
    void* m_DstBuffer;
};

#endif // JACKMIDIHANDLER_H
