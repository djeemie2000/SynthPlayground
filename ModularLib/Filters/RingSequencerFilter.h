#ifndef RingSequencerFILTER_H
#define RingSequencerFILTER_H

#include <vector>
#include "AudioFilterI.h"
#include "RingSequencer.h"

class CRingSequencerFilter : public IAudioFilter
{
public:
    CRingSequencerFilter();

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

private:
    CRingSequencer<float> m_RingSequencer;
    std::vector<float> m_DefaultTrigger;
    std::vector<float> m_DefaultStep;
};

#endif // RingSequencerFILTER_H
