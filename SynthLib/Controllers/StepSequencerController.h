#ifndef STEPSEQUENCERCONTROLLER_H
#define STEPSEQUENCERCONTROLLER_H

#include <memory>
#include "MidiSourceI.h"
#include "StepSequencer2.h"

class IMidiHandler;

class CStepSequencerController : public IMidiSource
{
public:
    CStepSequencerController(int SamplingFrequency, std::shared_ptr<IMidiHandler> MidiInputHandler, std::shared_ptr<IMidiSource> MidiSource);

    int OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp) override;

    // Step sequencer
    int GetMaxNumSteps() const;
    void SetActive(int Step, bool IsActive);
    void SetOctave(int Step, EOctave Octave);
    void SetNote(int Step, ENote Note);
    void SetBeatsPerMinute(int Bpm);
    void SetBarsPerBeat(int BarsPerBeat);
    void SetNumSteps(int NumSteps);
    void Start();
    void Stop();
    void SetDuration(int DurationPercentage);
    void SetStepSize(int StepSize);

private:
    std::shared_ptr<IMidiHandler> m_MidiInputHandler;
    std::shared_ptr<IMidiSource> m_MidiSource;
    CStepSequencer2<float, 16> m_StepSequencer;
    CStepSequencer2<float, 16>::SStep m_CurrentStep;
    bool    m_IsActive;
    int     m_Counter;
    int     m_StepSize;
};

#endif // STEPSEQUENCERCONTROLLER_H
