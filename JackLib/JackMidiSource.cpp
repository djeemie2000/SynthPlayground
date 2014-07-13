#include "JackMidiSource.h"
#include <jack/midiport.h>

CJackMidiSource::CJackMidiSource()
 : m_RingBuffer(0)
{
    const int RingBufferSize = 1<<14;
    m_RingBuffer = jack_ringbuffer_create(RingBufferSize);
    m_IntermediateBuffer.assign(RingBufferSize, 0);
}

CJackMidiSource::~CJackMidiSource()
{
    jack_ringbuffer_free(m_RingBuffer);
}

namespace
{

int WriteToRingBuffer(jack_ringbuffer_t* RingBuffer, std::uint32_t TimeStamp, const std::vector<unsigned char>& Data)
{
    int DataSize = Data.size();
    int NumWritten = jack_ringbuffer_write(RingBuffer, (const char*)(&TimeStamp), sizeof(TimeStamp));
    NumWritten += jack_ringbuffer_write(RingBuffer, (const char*)(&DataSize), sizeof(DataSize));
    NumWritten += jack_ringbuffer_write(RingBuffer, (const char*)Data.data(), Data.size());
    return NumWritten;
}

int ReadFromRingBuffer(jack_ringbuffer_t* RingBuffer, std::uint32_t& TimeStamp, std::vector<unsigned char>& Data)
{
    int DataSize = 0;
    int NumRead = jack_ringbuffer_read(RingBuffer, (char*)(&TimeStamp), sizeof(TimeStamp))
                + jack_ringbuffer_read(RingBuffer, (char*)(&DataSize), sizeof(DataSize));
    Data.resize(DataSize);
    NumRead += jack_ringbuffer_read(RingBuffer, (char*)Data.data(), DataSize);
    return NumRead;
}

}

int CJackMidiSource::OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp)
{
    // write stack of midi events into the DstBuffer
    // let's hope the jack ringbuffer does its job
    while (0< jack_ringbuffer_read_space(m_RingBuffer))
    {
        std::uint32_t TimeStamp = 0;
        if(0<ReadFromRingBuffer(m_RingBuffer, TimeStamp, m_IntermediateBuffer))
        {
            jack_midi_event_write(Dst, TimeStamp, (const jack_midi_data_t*)m_IntermediateBuffer.data(), m_IntermediateBuffer.size());
        }
    }

    return 0;
}

void CJackMidiSource::OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp)
{
    WriteToRingBuffer(m_RingBuffer, TimeStamp, { 0x90, Note & 0x7F, Velocity });
}

void CJackMidiSource::OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp)
{
    WriteToRingBuffer(m_RingBuffer, TimeStamp, { 0x80, Note, Velocity });
}

void CJackMidiSource::OnController(int Parameter, int Value, std::uint32_t TimeStamp)
{
    WriteToRingBuffer(m_RingBuffer, TimeStamp, { 0xB0, Parameter, Value });
}

void CJackMidiSource::OnPitchbend(int Value, std::uint32_t TimeStamp)
{
    WriteToRingBuffer(m_RingBuffer, TimeStamp, { 0xB0, 0, Value });
}

void CJackMidiSource::OnUnknown(std::uint32_t )
{
    //ignore
}
