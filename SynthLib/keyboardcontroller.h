#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include <memory>
#include "NoteHandlerI.h"

class IMidiInputHandler;

class CKeyboardController : public INoteHandler
{
public:
    CKeyboardController(std::shared_ptr<IMidiInputHandler> Handler);

    void OnNoteOn(ENote Note, EOctave Octave) override;
    void OnNoteOff(ENote Note, EOctave Octave) override;

private:
    std::shared_ptr<IMidiInputHandler> m_Handler;
};

#endif // KEYBOARDCONTROLLER_H
