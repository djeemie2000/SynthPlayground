#ifndef STEPSEQUENCERCONTROLLER_H
#define STEPSEQUENCERCONTROLLER_H

#include <memory>
#include "StepSequencerI.h"
#include "MidiSourceI.h"
#include "StepSequencer2.h"
#include "PeriodicTicker.h"

class IMidiInputHandler;

class CStepSequencerController : public IStepSequencer
                                , public IMidiSource
{
public:
    CStepSequencerController(int SamplingFrequency, std::shared_ptr<IMidiInputHandler> MidiInputHandler, std::shared_ptr<IMidiSource> MidiSource);

    int OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp) override;

    // Step sequencer
    int NumSteps() const override;
    void SetActive(int Step, bool IsActive) override;
    void SetOctave(int Step, EOctave Octave) override;
    void SetNote(int Step, ENote Note) override;
    void SetBeatsPerMinute(int Bpm) override;
    void SetBarsPerBeat(int BarsPerBeat) override;
    void Start() override;
    void Stop() override;

private:
    std::shared_ptr<IMidiInputHandler> m_MidiInputHandler;
    std::shared_ptr<IMidiSource> m_MidiSource;
    CStepSequencer2<float, 8> m_StepSequencer;
    CStepSequencer2<float, 8>::SStep m_CurrentStep;
    CPeriodicTicker m_StepSequencerTicker;
    bool    m_IsActive;
};

#endif // STEPSEQUENCERCONTROLLER_H
