#include <vector>
#include "JackMidiHandler.h"
#include <jack/midiport.h>


CJackMidiHandler::CJackMidiHandler(void* DstBuffer)
 : m_DstBuffer(DstBuffer)
{
}

void CJackMidiHandler::OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp)
{
    std::vector<jack_midi_data_t> TmpBuffer = { 0x90, static_cast<jack_midi_data_t>(Note & 0x7F), static_cast<jack_midi_data_t>(Velocity) };
    jack_midi_event_write(m_DstBuffer, TimeStamp, TmpBuffer.data(), TmpBuffer.size());
}

void CJackMidiHandler::OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp)
{
    std::vector<jack_midi_data_t> TmpBuffer = { 0x80, static_cast<jack_midi_data_t>(Note & 0x7F), static_cast<jack_midi_data_t>(Velocity) };
    jack_midi_event_write(m_DstBuffer, TimeStamp, TmpBuffer.data(), TmpBuffer.size());
}

void CJackMidiHandler::OnController(int Parameter, int Value, std::uint32_t TimeStamp)
{
    std::vector<jack_midi_data_t> TmpBuffer = { 0xB0, static_cast<jack_midi_data_t>(Parameter), static_cast<jack_midi_data_t>(Value) };
    jack_midi_event_write(m_DstBuffer, TimeStamp, TmpBuffer.data(), TmpBuffer.size());
}

void CJackMidiHandler::OnPitchbend(int Value, std::uint32_t TimeStamp)
{
    // ??? scaling ?????????????????
    std::vector<jack_midi_data_t> TmpBuffer = { 0xE0, 0, static_cast<jack_midi_data_t>(Value & 0x7F) };
    jack_midi_event_write(m_DstBuffer, TimeStamp, TmpBuffer.data(), TmpBuffer.size());
}

void CJackMidiHandler::OnUnknown(std::uint32_t /*TimeStamp*/)
{
    // do nothing
}
