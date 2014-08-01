#ifndef RINGSEQUENCERMIDICONTROLLERSTEP_H
#define RINGSEQUENCERMIDICONTROLLERSTEP_H

#include <cstdint>

class IMidiInputHandler;

class CRingSequencerMidiControllerStep
{
public:
    CRingSequencerMidiControllerStep();

    void SetMidiController(int MidiController);
    void SetStep(int Step);
    void SetStart(int Start);
    void SetMin(int Min);
    void SetMax(int Max);
    void SetActive(bool Active);
    void Apply(IMidiInputHandler& Handler, std::uint32_t TimeStamp);

private:
    void Update();

    int m_MidiController;
    bool m_Active;
    int m_Min;
    int m_Max;
    int m_Step;
    int m_Start;
    int m_Value;
};

#endif // RINGSEQUENCERMIDICONTROLLERSTEP_H
