#ifndef MULTIMIDIHANDLER_H
#define MULTIMIDIHANDLER_H

#include <vector>
#include <memory>
#include "MidiHandlerI.h"

class CMultiMidiHandler : public IMidiHandler
{
public:
    CMultiMidiHandler();

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

    void AddHandler(std::shared_ptr<IMidiHandler> Handler);

private:
    std::vector<std::shared_ptr<IMidiHandler>> m_Handlers;
};

#endif // MULTIMIDIHANDLER_H
