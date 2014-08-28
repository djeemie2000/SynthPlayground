#ifndef PHASORFILTER_H
#define PHASORFILTER_H

#include "AudioFilterI.h"
#include "PhaseStep.h"
#include "PhaseGenerator.h"

class CPhasorFilter : public IAudioFilter
{
public:
    CPhasorFilter(int SamplingFrequency);

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

private:
    CPhaseStep<float> m_PhaseStep;
    CPhaseGenerator<float> m_PhaseGenerator;
};

#endif // PHASORFILTER_H