#ifndef TRIGGERMIDINOTEHANDLER_H
#define TRIGGERMIDINOTEHANDLER_H

#include "MidiInputHandlerI.h"

class CTriggerMidiNoteHandler : public IMidiInputHandler
{
public:
    CTriggerMidiNoteHandler();

    void OnStart(float* FreqBuffer, float* TriggerBuffer, std::uint32_t NumFrames);

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

    void OnFinish();

private:
    void FillBuffers(float Frequency, float Trigger, std::uint32_t End); //!< fill buffers from m_CurrentStep up to End

    float m_Frequency;
    float* m_FreqBuffer;
    float* m_TriggerBuffer;
    std::uint32_t m_NumFrames;
    std::uint32_t m_CurrentStep;

};

#endif // TRIGGERMIDINOTEHANDLER_H
