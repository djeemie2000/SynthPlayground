#ifndef RINGSEQUENCERCONTROLLER_H
#define RINGSEQUENCERCONTROLLER_H

#include <memory>
#include <vector>
#include "MidiSourceI.h"
#include "BpmPeriod.h"
#include "RingSequencerMidiControllerStep.h"

class IMidiHandler;

class CRingSequencerController : public IMidiSource
{
public:
    CRingSequencerController(int SamplingFrequency, std::shared_ptr<IMidiHandler> MidiInputHandler, std::shared_ptr<IMidiSource> MidiSource);

    int OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp) override;

    void SetBeatsPerMinute(int Bpm);
    void SetBarsPerBeat(int BarsPerBeat);
    void Activate(bool Active);

    void SetMidiController(int Idx, int MidiController);
    void SetStep(int Idx, int Step);
    void SetStart(int Idx, int Start);
    void SetMin(int Idx, int Min);
    void SetMax(int Idx, int Max);
    void SetActive(int Idx, bool Active);

private:
    bool CheckResize(int Idx);

    std::shared_ptr<IMidiHandler>  m_MidiInputHandler;
    std::shared_ptr<IMidiSource>        m_MidiSource;
    int                                 m_Counter;
    CBpmPeriod                          m_PeriodSamples;
    bool                                m_Active;
    std::vector<CRingSequencerMidiControllerStep> m_MidiControllerStep;
};

#endif // RINGSEQUENCERCONTROLLER_H
