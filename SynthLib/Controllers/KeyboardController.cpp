#include "KeyboardController.h"
#include "MidiInputHandlerI.h"
#include "MidiNoteConverter.h"

CKeyboardController::CKeyboardController(std::shared_ptr<IMidiHandler> Handler)
 : m_Handler(Handler)
{
}

void CKeyboardController::OnNoteOn(ENote Note, EOctave Octave)
{
    m_Handler->OnNoteOn(CMidiNoteConverter().ToMidiNote(Note, Octave), 127, 0);
}

void CKeyboardController::OnNoteOff(ENote Note, EOctave Octave)
{
    m_Handler->OnNoteOff(CMidiNoteConverter().ToMidiNote(Note, Octave), 127, 0);
}
