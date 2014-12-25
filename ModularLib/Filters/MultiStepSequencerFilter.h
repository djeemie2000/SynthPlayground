#ifndef MultiStepSequencerFILTER_H
#define MultiStepSequencerFILTER_H

#include <functional>
#include "AudioFilterI.h"
#include "MultiStepSequencer.h"
#include "ClockPulse.h"
#include "Trigger.h"

class CMultiStepSequencerFilter : public IAudioFilter
{
public:
    typedef std::function<void (int)> CurrentStepCallbackType;

    static const int NumSequencerSteps = 8;

    CMultiStepSequencerFilter(int SamplingFrequency, CurrentStepCallbackType Callback);

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  const std::vector<std::shared_ptr<IMidiHandler>> MidiHandlers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    int GetMaxNumSteps() const;

    void SetNote(int Step, ENote Note);
    void SetOctave(int Step, EOctave Octave);
    void SetStepMode(int Step, int Mode);

    void SetStepSize(int StepSize);
    void SetStepIntervalLength(int Length);

    void SetActive(bool Active);

private:
    CClockPulseIn<float>                            m_ClockIn;
    CMultiStepSequencer<float, NumSequencerSteps>   m_MultiStepSequencer;
    CGateToTrigger<float>                           m_GateToTrigger;
    float   m_Gate;
    float   m_Frequency;
    float   m_Velocity;
    CurrentStepCallbackType m_Callback;
};

#endif // MultiStepSequencerFILTER_H
