#ifndef StepSequencerFILTER_H
#define StepSequencerFILTER_H

#include <functional>
#include "AudioFilterI.h"
#include "StepSequencer2.h"

class CStepSequencerFilter : public IAudioFilter
{
public:
    typedef std::function<void (int)> CurrentStepCallbackType;

    static const int NumSequencerSteps = 16;

    CStepSequencerFilter(int SamplingFrequency, CurrentStepCallbackType Callback);

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
    void SetActive(int Step, bool IsActive);
    void SetOctave(int Step, EOctave Octave);
    void SetNote(int Step, ENote Note);
    void SetStepSize(int StepSize);
    void SetActive(bool Active);
    void SetNumSteps(int NumSteps);

private:
    CStepSequencer2<float, NumSequencerSteps>          m_StepSequencer;
    CStepSequencer2<float, NumSequencerSteps>::SStep   m_CurrentStep;
    bool    m_IsActive;
    int     m_StepSize;
    float   m_Frequency;
    CurrentStepCallbackType m_Callback;
};

#endif // StepSequencerFILTER_H
