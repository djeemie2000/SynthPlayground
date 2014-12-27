#ifndef TRIGGERMIDINOTEHANDLER_H
#define TRIGGERMIDINOTEHANDLER_H

#include "MidiHandlerI.h"

class CTriggerMidiNoteHandler : public IMidiHandler
{
public:
    CTriggerMidiNoteHandler();

    void OnStart(float* FreqBuffer, float* TriggerBuffer, float* VelocityBuffer, std::uint32_t NumFrames);

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

    void OnFinish();

private:
    void FillBuffers(float Frequency, float Trigger, float Velocity, std::uint32_t End); //!< fill buffers from m_CurrentStep up to End

    float m_Frequency;
    float m_Velocity;
    float* m_FreqBuffer;
    float* m_TriggerBuffer;
    float* m_VelocityBuffer;
    std::uint32_t m_NumFrames;
    std::uint32_t m_CurrentStep;

};

#endif // TRIGGERMIDINOTEHANDLER_H
