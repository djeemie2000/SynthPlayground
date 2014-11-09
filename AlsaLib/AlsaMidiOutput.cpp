#include <iostream>
#include "AlsaMidiOutput.h"

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

CAlsaMidiOutput::CAlsaMidiOutput()
    : m_MidiSequencerHandle(0)
    , m_MidiOutputPort(-1)
    , m_IsOpen(false)
{
}

CAlsaMidiOutput::~CAlsaMidiOutput()
{
    // close if needed!
    Close();
}

bool CAlsaMidiOutput::Open(const std::string &ClientName, const std::string &PortName)
{
    if(OpenMidiOutput(ClientName, PortName))
    {
        m_IsOpen = true;
    }
    return m_IsOpen;
}

void CAlsaMidiOutput::Close()
{
    if(m_IsOpen)
    {
        CloseMidiOutput();
        m_IsOpen = false;
    }
}

void CAlsaMidiOutput::OnNoteOn(int Note, int Velocity, std::uint32_t /*TimeStamp*/)
{
    snd_seq_event_t ev;
    snd_seq_ev_clear(&ev);
    snd_seq_ev_set_direct(&ev);
    snd_seq_ev_set_source(&ev, m_MidiOutputPort);
    snd_seq_ev_set_subs(&ev);

    int channel = 0;
    snd_seq_ev_set_noteon(&ev, channel, Note, Velocity);

    WriteMidiEvent(ev);
}

void CAlsaMidiOutput::OnNoteOff(int Note, int Velocity, std::uint32_t /*TimeStamp*/)
{
    snd_seq_event_t ev;
    snd_seq_ev_clear(&ev);
    snd_seq_ev_set_direct(&ev);
    snd_seq_ev_set_source(&ev, m_MidiOutputPort);
    snd_seq_ev_set_subs(&ev);

    int channel = 0;
    snd_seq_ev_set_noteoff(&ev, channel, Note, Velocity);

    WriteMidiEvent(ev);
}

void CAlsaMidiOutput::OnController(int Parameter, int Value, std::uint32_t /*TimeStamp*/)
{
    snd_seq_event_t ev;
    snd_seq_ev_clear(&ev);
    snd_seq_ev_set_direct(&ev);
    snd_seq_ev_set_source(&ev, m_MidiOutputPort);
    snd_seq_ev_set_subs(&ev);

    int channel = 0;
    snd_seq_ev_set_controller(&ev, channel, Parameter, Value);

    WriteMidiEvent(ev);
}

void CAlsaMidiOutput::OnPitchbend(int Value, std::uint32_t /*TimeStamp*/)
{
    snd_seq_event_t ev;
    snd_seq_ev_clear(&ev);
    snd_seq_ev_set_direct(&ev);
    snd_seq_ev_set_source(&ev, m_MidiOutputPort);
    snd_seq_ev_set_subs(&ev);

    int channel = 0;
    snd_seq_ev_set_pitchbend(&ev, channel, Value);

    WriteMidiEvent(ev);
}

void CAlsaMidiOutput::OnUnknown(std::uint32_t /*TimeStamp*/)
{
    //do nothing
}

bool CAlsaMidiOutput::OpenMidiOutput(const std::string& ClientName, const std::string& PortName)
{
    return CheckMidiCommand(snd_seq_open(&m_MidiSequencerHandle, "default", SND_SEQ_OPEN_OUTPUT, SND_SEQ_NONBLOCK), "Could not open sequencer")
            && CheckMidiCommand(snd_seq_set_client_name(m_MidiSequencerHandle, ClientName.c_str()), "Could not set client name")
            && CheckMidiCommand(m_MidiOutputPort = snd_seq_create_simple_port(m_MidiSequencerHandle, PortName.c_str(), SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, SND_SEQ_PORT_TYPE_APPLICATION), "Could not open port");
}

bool CAlsaMidiOutput::CloseMidiOutput()
{
    return CheckMidiCommand(snd_seq_nonblock(m_MidiSequencerHandle, SND_SEQ_NONBLOCK), "Could not set non-blocking mode")//set to non-blocking mode so thread can stop
            && CheckMidiCommand(snd_seq_delete_simple_port(m_MidiSequencerHandle, m_MidiOutputPort), "Could not delete port")
            && CheckMidiCommand(snd_seq_close(m_MidiSequencerHandle), "Could not close sequencer");
}

void CAlsaMidiOutput::WriteMidiEvent(snd_seq_event_t& ev)
{
    snd_seq_event_output_direct(m_MidiSequencerHandle, &ev);
    snd_seq_drain_output(m_MidiSequencerHandle);
}
