#include "TriggerMidiNoteHandler.h"
#include "Pitch.h"
#include "MidiNotePitch.h"

CTriggerMidiNoteHandler::CTriggerMidiNoteHandler()
 : m_Frequency(440.0f)
 , m_Velocity(0.0f)
 , m_FreqBuffer(0)
 , m_TriggerBuffer(0)
 , m_VelocityBuffer(0)
 , m_NumFrames(0)
 , m_CurrentStep(0)
{
}

void CTriggerMidiNoteHandler::OnStart(float *FreqBuffer, float *TriggerBuffer, float *VelocityBuffer, std::uint32_t NumFrames)
{
    m_CurrentStep = 0;
    m_NumFrames = NumFrames;
    m_FreqBuffer = FreqBuffer;
    m_TriggerBuffer = TriggerBuffer;
    m_VelocityBuffer = VelocityBuffer;
    // for ease of use, already fill trigger with all zeros
    if(m_TriggerBuffer)
    {
        std::fill(m_TriggerBuffer, m_TriggerBuffer+m_NumFrames, 0.0f);
    }
}

void CTriggerMidiNoteHandler::OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp)
{
    float Frequency = CMidiNotePitch()(Note);
    float Vel = Velocity/127.0;
    FillBuffers(Frequency, 1.0f, Vel, TimeStamp);
}

void CTriggerMidiNoteHandler::OnNoteOff(int /*Note*/, int Velocity, std::uint32_t TimeStamp)
{
    float Vel = Velocity/127.0;
    FillBuffers(m_Frequency, -1.0f, Vel, TimeStamp);
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
    FillBuffers(m_Frequency, 0.0f, m_Velocity, m_NumFrames);

    m_FreqBuffer = 0;
    m_TriggerBuffer = 0;
    m_VelocityBuffer = 0;
}

void CTriggerMidiNoteHandler::FillBuffers(float Frequency, float Trigger, float Velocity, std::uint32_t End)
{
    // from current step up to end: fill freq buffer with current freq, then remember changed frequency
    // set trigger value in buffer[End]
    // remember End as m_CurrentStep
    if(m_FreqBuffer)
    {
        std::fill(m_FreqBuffer+m_CurrentStep, m_FreqBuffer+End, m_Frequency);
    }
    if(m_VelocityBuffer)
    {
        std::fill(m_VelocityBuffer+m_CurrentStep, m_VelocityBuffer+End, m_Velocity);
    }
    if(m_TriggerBuffer && End<=m_NumFrames)
    {
        m_TriggerBuffer[End] = Trigger;
    }
    m_Frequency = Frequency;
    m_Velocity = Velocity;
    m_CurrentStep = End;
}
