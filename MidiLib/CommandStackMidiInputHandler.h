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

    void OnNoteOn(int Note, int Velocity) override;
    void OnNoteOff(int Note, int ) override;
    void OnController(int Parameter, int Value) override;
    void OnPitchbend(int Value) override;
    void OnUnknown() override;

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
