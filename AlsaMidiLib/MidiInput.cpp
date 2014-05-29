#include <iostream>
#include "MidiInput.h"
#include "MidiInputHandlerI.h"

namespace
{

bool CheckMidiCommand(int ReturnValue, const std::string& msg)
{
    if(ReturnValue < 0)
    {
        std::cerr << "ERROR: " << msg;
        return false;
    }
    return true;
}

}

CMidiInput::CMidiInput(IMidiInputHandler &Handler)
 : m_Handler(Handler)
 , m_MidiSequencerHandle(0)
 , m_MidiInputPort(-1)
{
}

CMidiInput::~CMidiInput()
{
    //TODO close if needed!
}

bool CMidiInput::OpenMidiInput(const std::string& ClientName, const std::string& PortName)
{
    return CheckMidiCommand(snd_seq_open(&m_MidiSequencerHandle, "default", SND_SEQ_OPEN_INPUT, 0), "Could not open sequencer")
        && CheckMidiCommand(snd_seq_set_client_name(m_MidiSequencerHandle, ClientName.c_str()), "Could not set client name")
            && CheckMidiCommand(m_MidiInputPort = snd_seq_create_simple_port(m_MidiSequencerHandle, PortName.c_str(), SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, SND_SEQ_PORT_TYPE_APPLICATION), "Could not open port");
}

bool CMidiInput::CloseMidiInput()
{
    return CheckMidiCommand(snd_seq_delete_simple_port(m_MidiSequencerHandle, m_MidiInputPort), "Could not delete port")
            && CheckMidiCommand(snd_seq_close(m_MidiSequencerHandle), "Could not close sequencer");
}

void CMidiInput::Start()
{
    //TODO start thread!
}

void CMidiInput::Stop()
{
    // TODO stop thread
}

void CMidiInput::Run()
{
    ProcessMidiEvent(ReadMidiEvent());
}

snd_seq_event_t* CMidiInput::ReadMidiEvent() const
{
    snd_seq_event_t *ev = 0;
    snd_seq_event_input(m_MidiSequencerHandle, &ev);
    return ev;
}

void CMidiInput::ProcessMidiEvent(const snd_seq_event_t *ev)
{
    if(ev->type == SND_SEQ_EVENT_NOTEON)
    {
        m_Handler.OnNoteOn(ev->data.note.note, ev->data.note.velocity);
    }
    else if(ev->type == SND_SEQ_EVENT_NOTEOFF)
    {
        m_Handler.OnNoteOff(ev->data.note.note, ev->data.note.velocity);
    }
    else if(ev->type == SND_SEQ_EVENT_CONTROLLER)
    {
        m_Handler.OnController(ev->data.control.param, ev->data.control.value);
    }
    else if(ev->type == SND_SEQ_EVENT_PITCHBEND)
    {
        m_Handler.OnPitchbend(ev->data.control.value);
    }
    else
    {
        m_Handler.OnUnknown();
    }
}
