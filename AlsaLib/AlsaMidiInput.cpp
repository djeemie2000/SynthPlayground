#include <iostream>
#include "AlsaMidiInput.h"
#include "MidiInputHandlerI.h"
#include "PeriodicThreadRunner.h"

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

CAlsaMidiInput::CAlsaMidiInput(IMidiHandler &Handler)
    : m_Handler(Handler)
    , m_MidiSequencerHandle(0)
    , m_MidiInputPort(-1)
    , m_IsOpen(false)
{
    m_ThreadRunner.reset(new CPeriodicThreadRunner<CAlsaMidiInput>(*this));
    m_ThreadRunner->SetPeriod(1);//1mSec??
}

CAlsaMidiInput::~CAlsaMidiInput()
{
    // close if needed!
    Close();
}

bool CAlsaMidiInput::Open(const std::string &ClientName, const std::string &PortName)
{
    if(OpenMidiInput(ClientName, PortName))
    {
        m_IsOpen = true;
        StartListening();
    }
    return m_IsOpen;
}

void CAlsaMidiInput::Close()
{
    if(m_IsOpen)
    {
        StopListening();
        CloseMidiInput();
        m_IsOpen = false;
    }
}

bool CAlsaMidiInput::OpenMidiInput(const std::string& ClientName, const std::string& PortName)
{
    return CheckMidiCommand(snd_seq_open(&m_MidiSequencerHandle, "default", SND_SEQ_OPEN_INPUT, SND_SEQ_NONBLOCK), "Could not open sequencer")
            && CheckMidiCommand(snd_seq_set_client_name(m_MidiSequencerHandle, ClientName.c_str()), "Could not set client name")
            && CheckMidiCommand(m_MidiInputPort = snd_seq_create_simple_port(m_MidiSequencerHandle, PortName.c_str(), SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, SND_SEQ_PORT_TYPE_APPLICATION), "Could not open port");
}

bool CAlsaMidiInput::CloseMidiInput()
{
    return CheckMidiCommand(snd_seq_nonblock(m_MidiSequencerHandle, SND_SEQ_NONBLOCK), "Could not set non-blocking mode")//set to non-blocking mode so thread can stop
            && CheckMidiCommand(snd_seq_delete_simple_port(m_MidiSequencerHandle, m_MidiInputPort), "Could not delete port")
            && CheckMidiCommand(snd_seq_close(m_MidiSequencerHandle), "Could not close sequencer");
}

void CAlsaMidiInput::StartListening()
{
    m_ThreadRunner->Start();
}

void CAlsaMidiInput::StopListening()
{
    m_ThreadRunner->Stop();
}

void CAlsaMidiInput::OnTick()
{
    if(m_IsOpen)
    {
        int RemainingBufferSize = 1;
        while(0<RemainingBufferSize)
        {
            ProcessMidiEvent(ReadMidiEvent(RemainingBufferSize));
        }
    }
}

snd_seq_event_t* CAlsaMidiInput::ReadMidiEvent(int &RemainingBufferSize) const
{
    snd_seq_event_t *ev = 0;
    RemainingBufferSize = snd_seq_event_input(m_MidiSequencerHandle, &ev);
    return ev;
}

void CAlsaMidiInput::ProcessMidiEvent(const snd_seq_event_t *ev)
{
    if(ev)
    {
        if(ev->type == SND_SEQ_EVENT_NOTEON)
        {
            m_Handler.OnNoteOn(ev->data.note.note, ev->data.note.velocity, ev->time.tick);
        }
        else if(ev->type == SND_SEQ_EVENT_NOTEOFF)
        {
            m_Handler.OnNoteOff(ev->data.note.note, ev->data.note.velocity, ev->time.tick);
        }
        else if(ev->type == SND_SEQ_EVENT_CONTROLLER)
        {
            m_Handler.OnController(ev->data.control.param, ev->data.control.value, ev->time.tick);
        }
        else if(ev->type == SND_SEQ_EVENT_PITCHBEND)
        {
            m_Handler.OnPitchbend(ev->data.control.value, ev->time.tick);
        }
        else
        {
            m_Handler.OnUnknown(ev->time.tick);
        }
    }
}
