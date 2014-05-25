#include <iostream>

#include <unistd.h>

#include <jack/jack.h>
#include <jack/midiport.h>

using namespace std;

struct SJackState
{
    jack_port_t * s_MidInputPort;

    SJackState()
        : s_MidInputPort(0)
    {

    }
};

void OnJackShutdown(void* )
{
    cout << "Jack shutdown!" << endl;
    exit(1);
}

int OnProcess(jack_nframes_t nframes, void *arg)
{
    cout << "Jack process " << nframes << endl;
    SJackState* State = (SJackState*)(arg);

    void* MidiInputBuffer = jack_port_get_buffer(State->s_MidInputPort, nframes);
    jack_nframes_t NumMidiEvents = jack_midi_get_event_count(MidiInputBuffer);

    cout << "received " << NumMidiEvents << " midi events! " << endl;

    for(jack_nframes_t idx = 0; idx<NumMidiEvents; ++idx)
    {
        jack_midi_event_t MidiEvent;
        jack_midi_event_get(&MidiEvent, MidiInputBuffer, idx);

        cout << "Midi event " << idx << ": ";
        cout << "timestamp= " << MidiEvent.time << endl;
        cout << "size= " << MidiEvent.size << endl;
        int FirstByte = (*MidiEvent.buffer) & 0xFF;
        cout << std::hex << FirstByte << endl;
    }

    return 0;
}

int main()
{
    cout << "Hello World!" << endl;


    jack_client_t *client = jack_client_open ("JackTest", JackNullOption, NULL);
    if(client)
    {
        SJackState* State = new SJackState();

        cout << "registering midi input port" << endl;
        State->s_MidInputPort = jack_port_register (client, "midi_in", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);

        cout << "Creating process callback..." << endl;
        jack_set_process_callback (client, OnProcess, State);

        std::cout << "configuring shutdown..." << endl;
        jack_on_shutdown (client, OnJackShutdown, State);

        cout << "Activating client..." << endl;
        if (jack_activate (client))
        {
            cout << "cannot activate client!" << endl;
        }

        int bs = 0;
        for(int Cntr = 0; Cntr<10*100; ++Cntr)
        {
            sleep(10);
            bs += 2;
        }
        cout << bs << endl;

        std::cout << "closing jack client..." << endl;
        jack_client_close(client);

        delete State;
    }
    else
    {
        cout << "jack server not running?" << std::endl;
    }

    return 0;
}

