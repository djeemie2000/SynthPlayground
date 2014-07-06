#ifndef NOTEQUEUEMIDIINPUTHANDLER_H
#define NOTEQUEUEMIDIINPUTHANDLER_H

#include <list>
#include <utility>
#include <memory>
#include "MidiInputHandlerI.h"

class CNoteQueueMidiInputHandler : public IMidiInputHandler
{
public:
    CNoteQueueMidiInputHandler(std::shared_ptr<IMidiInputHandler> Handler);

    void OnNoteOn(int Note, int Velocity) override;
    void OnNoteOff(int Note, int Velocity) override;
    void OnController(int Parameter, int Value) override;
    void OnPitchbend(int Value) override;
    void OnUnknown() override;

private:
    struct SQueueItem
    {
        int s_Note;
        int s_Velocity;

        SQueueItem(int Note, int Velocity);
        bool operator ==(const SQueueItem& Other) const;
        bool operator !=(const SQueueItem& Other) const;
    };

    std::shared_ptr<IMidiInputHandler> m_Handler;
    std::list<SQueueItem> m_NoteQueue;

};

#endif // NOTEQUEUEMIDIINPUTHANDLER_H
