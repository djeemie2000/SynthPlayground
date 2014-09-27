#ifndef PeriodicTriggerFILTER_H
#define PeriodicTriggerFILTER_H

#include "AudioFilterI.h"
#include "StepSequencer2.h"

class CPeriodicTriggerFilter : public IAudioFilter
{
public:
    CPeriodicTriggerFilter(int SamplingFrequency);

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

    void SetBeatsPerMinute(int Bpm);
    void SetBeatsPerBar(int Bpb);
    void SetDuration(int DurationPercentage);

private:
    static const int NumSequencerSteps = 1;
    CStepSequencer2<float, NumSequencerSteps>   m_PeriodicTrigger;
    int m_Counter;
};

#endif // PeriodicTriggerFILTER_H
