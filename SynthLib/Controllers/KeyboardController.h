#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include <memory>
#include "NoteHandlerI.h"

class IMidiHandler;

class CKeyboardController : public INoteHandler
{
public:
    CKeyboardController(std::shared_ptr<IMidiHandler> Handler);

    void OnNoteOn(ENote Note, EOctave Octave) override;
    void OnNoteOff(ENote Note, EOctave Octave) override;

private:
    std::shared_ptr<IMidiHandler> m_Handler;
};

#endif // KEYBOARDCONTROLLER_H
