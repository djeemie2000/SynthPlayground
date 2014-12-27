#ifndef NOTEQUEUEMIDIINPUTHANDLER_H
#define NOTEQUEUEMIDIINPUTHANDLER_H

#include <cstdint>
#include <list>
#include <utility>
#include <memory>
#include "MidiHandlerI.h"

class CNoteQueueMidiInputHandler : public IMidiHandler
{
public:
    CNoteQueueMidiInputHandler(std::shared_ptr<IMidiHandler> Handler);

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

private:
    struct SQueueItem
    {
        int s_Note;
        int s_Velocity;
        std::uint32_t s_TimeStamp;

        SQueueItem(int Note, int Velocity, std::uint32_t TimeStamp);
        bool operator ==(const SQueueItem& Other) const;
        bool operator !=(const SQueueItem& Other) const;
    };

    std::shared_ptr<IMidiHandler> m_Handler;
    std::list<SQueueItem> m_NoteQueue;

};

#endif // NOTEQUEUEMIDIINPUTHANDLER_H
