#ifndef MIDIINPUTCONTROLLER_H
#define MIDIINPUTCONTROLLER_H

#include <memory>
#include "MidiInputHandlerI.h"
#include "MidiControllerHandlerI.h"

class CCommandStackController;

class CMidiInputController : public IMidiInputHandler, public IMidiControllerHandler
{
public:
    CMidiInputController(CCommandStackController &CommandStackController);

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

    bool Link(const std::string &ParameterName, int Parameter) override;
    void Add(const std::string &ParameterName, const HandlerFunction &Handler) override;

private:
    std::shared_ptr<IMidiInputHandler> m_MidiInputHandler;
    std::shared_ptr<IMidiControllerHandler> m_MidiControllerHandler;
    std::shared_ptr<IMidiInputHandler> m_MidiInputLogger;
};

#endif // MIDIINPUTCONTROLLER_H
