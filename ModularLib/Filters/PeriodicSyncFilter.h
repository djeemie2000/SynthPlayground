#ifndef PeriodicSyncFILTER_H
#define PeriodicSyncFILTER_H

#include "AudioFilterI.h"
#include "PeriodicTrigger.h"

class CPeriodicSyncFilter : public IAudioFilter
{
public:
    CPeriodicSyncFilter(int SamplingFrequency);

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

private:
    CPeriodicTrigger<float> m_Trigger;
};

#endif // PeriodicSyncFILTER_H
