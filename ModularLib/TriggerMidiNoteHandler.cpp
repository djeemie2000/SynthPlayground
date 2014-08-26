#include "TriggerMidiNoteHandler.h"
#include "Pitch.h"
#include "MidiNotePitch.h"

CTriggerMidiNoteHandler::CTriggerMidiNoteHandler()
 : m_Frequency(440.0f)
 , m_FreqBuffer(0)
 , m_TriggerBuffer(0)
 , m_NumFrames(0)
 , m_CurrentStep(0)
{
}

void CTriggerMidiNoteHandler::OnStart(float *FreqBuffer, float *TriggerBuffer, std::uint32_t NumFrames)
{
    m_CurrentStep = 0;
    m_NumFrames = NumFrames;
    m_FreqBuffer = FreqBuffer;
    m_TriggerBuffer = TriggerBuffer;
    // for ease of use, already fill trigger with all zeros
    std::fill(m_TriggerBuffer, m_TriggerBuffer+m_NumFrames, 0.0f);
}

void CTriggerMidiNoteHandler::OnNoteOn(int Note, int /*Velocity*/, std::uint32_t TimeStamp)
{
    float Frequency = CMidiNotePitch()(Note);
    FillBuffers(Frequency, 1.0f, TimeStamp);
}

void CTriggerMidiNoteHandler::OnNoteOff(int /*Note*/, int /*Velocity*/, std::uint32_t TimeStamp)
{
    FillBuffers(m_Frequency, -1.0f, TimeStamp);
}

void CTriggerMidiNoteHandler::OnController(int /*Parameter*/, int /*Value*/, std::uint32_t /*TimeStamp*/)
{

}

void CTriggerMidiNoteHandler::OnPitchbend(int /*Value*/, std::uint32_t /*TimeStamp*/)
{

}

void CTriggerMidiNoteHandler::OnUnknown(std::uint32_t /*TimeStamp*/)
{

}

void CTriggerMidiNoteHandler::OnFinish()
{
    FillBuffers(m_Frequency, 0.0f, m_NumFrames);
}

void CTriggerMidiNoteHandler::FillBuffers(float Frequency, float Trigger, std::uint32_t End)
{
    // from current step up to end: fill freq buffer with current freq, then remember changed frequency
    // set trigger value in buffer[End]
    // remember End as m_CurrentStep
    if(m_FreqBuffer)
    {
        std::fill(m_FreqBuffer+m_CurrentStep, m_FreqBuffer+End, m_Frequency);
    }
    if(m_TriggerBuffer && End<=m_NumFrames)
    {
        m_TriggerBuffer[End] = Trigger;
    }
    m_Frequency = Frequency;
    m_CurrentStep = End;
}
