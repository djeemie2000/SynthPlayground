#ifndef FMFILTER_H
#define FMFILTER_H

#include "AudioFilterI.h"
#include "FMFrequencyModulator.h"

class CFMFilter : public IAudioFilter
{
public:
    CFMFilter(int SamplingFrequency);

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

    void SelectModulatorWaveform(int Selection);

private:
    CFMFrequencyModulator<float> m_FM;
};

#endif // FMFILTER_H
