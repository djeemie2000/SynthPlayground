#include "JackMidiRenderer.h"
#include "MidiInputHandlerI.h"
#include <jack/midiport.h>

CJackMidiRenderer::CJackMidiRenderer(void *SrcBuffer)
 : m_SrcBuffer(SrcBuffer)
{
}

void CJackMidiRenderer::Accept(IMidiInputHandler &Handler)
{
    if(m_SrcBuffer)
    {
        jack_nframes_t NumEvents = jack_midi_get_event_count(m_SrcBuffer);
        if(0<NumEvents)
        {
            jack_nframes_t EventIndex = 0;
            while(EventIndex<NumEvents)
            {
                jack_midi_event_t MidiEvent;
                if(0==jack_midi_event_get(&MidiEvent, m_SrcBuffer, EventIndex))
                {
                    // handle:
                    // Note on  : 3 bytes 0x9x MidiNote [0,127] Velocity [0,127] -> msb always 0
                    // Note off : 3 bytes 0x8x MidiNote [0,127] Velocity [0,127] -> msb always 0
                    // Controll : 3 bytes 0xBx Param    [0,127] Value    [0,127] -> msb always 0
                    // Pitchbend: 3 bytes 0xEx Fine     [0,127] Coarse   [0,127] -> msb always 0
                    if(MidiEvent.size==3)
                    {
                        jack_midi_data_t TypeByte = MidiEvent.buffer[0] & 0xF0;
                        if(TypeByte==0x90)
                        {
                            Handler.OnNoteOn(MidiEvent.buffer[1], MidiEvent.buffer[2], MidiEvent.time);
                        }
                        else if(TypeByte==0x80)
                        {
                            Handler.OnNoteOff(MidiEvent.buffer[1], MidiEvent.buffer[2], MidiEvent.time);
                        }
                        else if(TypeByte==0xB0)
                        {
                            Handler.OnController(MidiEvent.buffer[1], MidiEvent.buffer[2], MidiEvent.time);
                        }
                        else if(TypeByte==0xE0)
                        {
                            Handler.OnPitchbend((MidiEvent.buffer[2]-64)<<7, MidiEvent.time);//fine?
                        }
                        else
                        {
                            Handler.OnUnknown(MidiEvent.time);
                        }
                    }
                    else
                    {
                        Handler.OnUnknown(MidiEvent.time);
                    }
                }
                ++EventIndex;
            }
        }
    }
}
