#ifndef MidiControllerValueHANDLER_H
#define MidiControllerValueHANDLER_H

#include "MidiHandlerI.h"

class CMidiControllerValueHandler : public IMidiHandler
{
public:
    CMidiControllerValueHandler();

    void OnStart(float* ValueBuffer, std::uint32_t NumFrames);

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

    void OnFinish();

    void SetParameter(int Parameter);
    void SetMin(float Min);
    void SetMax(float Max);

private:
    void FillBuffers(float Value, std::uint32_t End); //!< fill buffers from m_CurrentStep up to End
    float ToBufferValue(int Value) const;

    int m_Parameter;
    float m_Min;
    float m_Max;
    float m_BufferValue;
    float* m_ValueBuffer;
    std::uint32_t m_NumFrames;
    std::uint32_t m_CurrentStep;

};

#endif // MidiControllerValueHANDLER_H
