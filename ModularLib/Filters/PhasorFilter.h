#ifndef PHASORFILTER_H
#define PHASORFILTER_H

#include <vector>
#include "AudioFilterI.h"
#include "PhaseStep.h"
#include "PhaseAccumulator.h"

class CPhasorFilter : public IAudioFilter
{
public:
    CPhasorFilter(int SamplingFrequency);

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
    CPhaseStep<float> m_PhaseStep;
    CPhaseAccumulator<float> m_PhaseAccumulator;
    float m_PhaseStepSign;
    std::vector<float> m_DefaultFreq;
    std::vector<float> m_DefaultSync;
    std::vector<float> m_DefaultSoftSync;
};

#endif // PHASORFILTER_H
