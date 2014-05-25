#include <iostream>
#include <stdint.h>
#include <alsa/asoundlib.h>

using namespace std;

class IMidiInputHandler
{
public:
    virtual ~IMidiInputHandler(){}

    virtual void OnNoteOn(int Note, int Velocity) =0;
    virtual void OnNoteOff(int Note, int Velocity) =0;
    virtual void OnController(int Parameter, int Value) =0;
    virtual void OnPitchbend(int Value) =0;
    virtual void OnUnknown() =0;
};

class CLogMidiInputHandler : public IMidiInputHandler
{
public:
    CLogMidiInputHandler();

    void OnNoteOn(int Note, int Velocity) override;
    void OnNoteOff(int Note, int Velocity) override;
    void OnController(int Parameter, int Value) override;
    void OnPitchbend(int Value) override;
    void OnUnknown() override;
};

CLogMidiInputHandler::CLogMidiInputHandler()
{
}

void CLogMidiInputHandler::OnNoteOn(int Note, int Velocity)
{
    std::cout << "Note on  : " << std::hex << "0x" << Note << " vel(" << std::dec << Velocity << ")" << std::endl;
}

void CLogMidiInputHandler::OnNoteOff(int Note, int Velocity)
{
    std::cout << "Note off : " << std::hex << "0x" << Note << " vel(" << std::dec << Velocity << ")" << std::endl;
}

void CLogMidiInputHandler::OnController(int Parameter, int Value)
{
    std::cout << "Control  : " << std::hex << "0x" << Parameter << " val(" << std::dec << Value << ")" << std::endl;
}

void CLogMidiInputHandler::OnPitchbend(int Value)
{
    std::cout << "Pitchbend: " << " val(" << std::dec << Value << ")" << std::endl;
}

void CLogMidiInputHandler::OnUnknown()
{
    std::cout << "Unknown midi event" << std::endl;
}


bool CheckMidiCommand(int ReturnValue, const std::string& msg)
{
    if(ReturnValue < 0)
    {
        std::cerr << "ERROR: " << msg;
        return false;
    }
    return true;
}

class CMidiInput
{
public:
    CMidiInput(IMidiInputHandler& Handler);
    ~CMidiInput();

    bool OpenMidiInput(const string &ClientName, const string &PortName);
    bool CloseMidiInput();

    void Start();
    void Stop();
    void Run();

private:
    IMidiInputHandler& m_Handler;
    snd_seq_event_t *ReadMidiEvent() const;
    void ProcessMidiEvent(const snd_seq_event_t *ev);

    snd_seq_t*  m_MidiSequencerHandle;
    int         m_MidiInputPort;
};

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
//        printf("[%d] Note on: %2x vel(%2x)\n", ev->time.tick,
//                                               ev->data.note.note,
//                                               ev->data.note.velocity);
    }
    else if(ev->type == SND_SEQ_EVENT_NOTEOFF)
    {
        m_Handler.OnNoteOff(ev->data.note.note, ev->data.note.velocity);
//        printf("[%d] Note off: %2x vel(%2x)\n", ev->time.tick,
//                                               ev->data.note.note,
//                                               ev->data.note.velocity);
    }
    else if(ev->type == SND_SEQ_EVENT_CONTROLLER)
    {
        m_Handler.OnController(ev->data.control.param, ev->data.control.value);
//        printf("[%d] Control:  %2x val(%2x)\n", ev->time.tick,
//                                                ev->data.control.param,
//                                                ev->data.control.value);
    }
    else if(ev->type == SND_SEQ_EVENT_PITCHBEND)
    {
        m_Handler.OnPitchbend(ev->data.control.value);
//        printf("[%d] Pitchbend: %d\n", ev->time.tick, ev->data.control.value);
    }
    else
    {
        m_Handler.OnUnknown();
//        printf("[%d] Unknown:  Unhandled Event Received\n", ev->time.tick);
    }
}

int main()
{
    CLogMidiInputHandler Handler;
    CMidiInput MidiInput(Handler);
    if(MidiInput.OpenMidiInput("TestAlsa", "MidiIn"))
    {
        int Cntr = 40;
        while(0<Cntr)
        {
            MidiInput.Run();
            --Cntr;
        }
    }
    MidiInput.CloseMidiInput();
    return -1;
}
