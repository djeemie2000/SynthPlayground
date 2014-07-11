#ifndef COMMANDSTACKMIDIINPUTHANDLER_H
#define COMMANDSTACKMIDIINPUTHANDLER_H

#include <string>
#include <functional>
#include <map>
#include "MidiInputHandlerI.h"
#include "MidiControllerHandlerI.h"

class CCommandStackController;
struct SCmdStackItem;

class CCommandStackMidiInputHandler : public IMidiInputHandler, public IMidiControllerHandler
{
public:
    CCommandStackMidiInputHandler(CCommandStackController& CommandStackHandler);

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int , std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

    /*!
     * \brief Link a named parameter to a midi controller parameter
     * \param ParameterName
     * \param Parameter
     * \return
     */
    bool Link(const std::string& ParameterName, int Parameter) override;

    /*!
     * \brief Add a handler for a named parameter
     * \param ParameterName
     * \param Handler
     */
    void Add(const std::string& ParameterName, const HandlerFunction& Handler) override;

private:
    CCommandStackController& m_CommandStackHandler;

    std::map<std::string, HandlerFunction> m_Handlers;
    std::map<int, std::string> m_Links;
};

#endif // COMMANDSTACKMIDIINPUTHANDLER_H
