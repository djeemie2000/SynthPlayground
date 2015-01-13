#ifndef HpfFILTER_H
#define HpfFILTER_H

#include "AudioFilterI.h"
#include "OnePoleFilter.h"

class CHpfFilter : public IAudioFilter
{
public:
    CHpfFilter();

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

    void SetPoles(int Poles);
    void SetResonance(float Resonance);

private:
    CMultiStageFilter<float, COnePoleHighPassFilter<float>, 24> m_Hpfilter;
};

#endif // HpfFILTER_H
