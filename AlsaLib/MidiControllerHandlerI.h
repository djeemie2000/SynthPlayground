#ifndef MIDICONTROLLERHANDLERI_H
#define MIDICONTROLLERHANDLERI_H

#include <string>
#include <functional>

struct SCmdStackItem;

class IMidiControllerHandler
{
public:
    typedef std::function<void(SCmdStackItem& Item, int MidiControllerValue)> HandlerFunction;

    virtual ~IMidiControllerHandler() {}

    /*!
     * \brief Link a named parameter to a midi controller parameter
     * \param ParameterName
     * \param Parameter
     * \return
     */
    virtual bool Link(const std::string& ParameterName, int Parameter) =0;

    /*!
     * \brief Add a handler for a named parameter
     * \param ParameterName
     * \param Handler
     */
    virtual void Add(const std::string& ParameterName, const HandlerFunction& Handler) =0;

};

#endif // MIDICONTROLLERHANDLERI_H
