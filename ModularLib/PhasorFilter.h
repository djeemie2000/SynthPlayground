#ifndef PHASORFILTER_H
#define PHASORFILTER_H

#include "AudioFilterI.h"
#include "PhaseStep.h"

class CPhasorFilter : public IAudioFilter
{
public:
    CPhasorFilter(int SamplingFrequency);

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers, const std::vector<void*>& DestinationBuffers, int NumFrames, std::uint32_t TimeStamp) override;

private:
    CPhaseStep<float> m_PhaseStep;
};

#endif // PHASORFILTER_H
