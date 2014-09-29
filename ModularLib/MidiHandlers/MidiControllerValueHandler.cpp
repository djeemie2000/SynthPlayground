#include "MidiControllerValueHandler.h"
#include "Pitch.h"
#include "MidiNotePitch.h"

CMidiControllerValueHandler::CMidiControllerValueHandler()
 : m_Parameter(-1)
 , m_Min(0.0f)
 , m_Max(1.0f)
 , m_BufferValue(0.0f)
 , m_ValueBuffer(0)
 , m_NumFrames(0)
 , m_CurrentStep(0)
{
}

void CMidiControllerValueHandler::OnStart(float *ValueBuffer, std::uint32_t NumFrames)
{
    m_CurrentStep = 0;
    m_NumFrames = NumFrames;
    m_ValueBuffer = ValueBuffer;
}

void CMidiControllerValueHandler::OnNoteOn(int /*Note*/, int /*Velocity*/, std::uint32_t /*TimeStamp*/)
{
}

void CMidiControllerValueHandler::OnNoteOff(int /*Note*/, int /*Velocity*/, std::uint32_t /*TimeStamp*/)
{
}

void CMidiControllerValueHandler::OnController(int Parameter, int Value, std::uint32_t TimeStamp)
{
    if(Parameter==m_Parameter)
    {
        FillBuffers(ToBufferValue(Value), TimeStamp);
    }
}

void CMidiControllerValueHandler::OnPitchbend(int /*Value*/, std::uint32_t /*TimeStamp*/)
{

}

void CMidiControllerValueHandler::OnUnknown(std::uint32_t /*TimeStamp*/)
{

}

void CMidiControllerValueHandler::OnFinish()
{
    FillBuffers(m_BufferValue, m_NumFrames);
}

void CMidiControllerValueHandler::SetParameter(int Parameter)
{
    m_Parameter = Parameter;
}

void CMidiControllerValueHandler::SetMin(float Min)
{
    m_Min = Min;
}

void CMidiControllerValueHandler::SetMax(float Max)
{
    m_Max = Max;
}

void CMidiControllerValueHandler::FillBuffers(float Value, std::uint32_t End)
{
    // from current step up to end: fill freq buffer with current value, then remember changed value
    // remember End as m_CurrentStep
    if(m_ValueBuffer)
    {
        std::fill(m_ValueBuffer+m_CurrentStep, m_ValueBuffer+End, m_BufferValue);
    }
    m_BufferValue = Value;
    m_CurrentStep = End;
}

float CMidiControllerValueHandler::ToBufferValue(int Value) const
{
    // value is in [0, 127]
    // currently only linear conversion is supported with adjustable min and max
    return  m_Min + (m_Max-m_Min)*Value/127.0f;
}
