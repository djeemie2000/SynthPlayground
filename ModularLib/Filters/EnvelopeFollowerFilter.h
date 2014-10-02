#ifndef EnvelopeFollowerFILTER_H
#define EnvelopeFollowerFILTER_H

#include "AudioFilterI.h"
#include "EnvelopeFollower.h"

class CEnvelopeFollowerFilter : public IAudioFilter
{
public:
    CEnvelopeFollowerFilter(int SamplingFrequency);

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

    void SetAttack(float AttackMilliSeconds);
    void SetRelease(float ReleaseMilliSeconds);

private:
    CEnvelopeFollower<float> m_EnvelopeFollower;
};

#endif // EnvelopeFollowerFILTER_H
