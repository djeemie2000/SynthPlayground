#ifndef ADSRENVELOPEBANKFILTER_H
#define ADSRENVELOPEBANKFILTER_H
#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"
#include "ConstNumSamplesGenerator.h"
#include "ADSREnvelope.h"

class CADSREnvelopeBankFilter : public IAudioFilter
{
public:
    CADSREnvelopeBankFilter(int Size, int SamplingFrequency);

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    void SetAttackMilliSeconds(int Index, float Attack);
    void SetDecayMilliSeconds(int Index, float Decay);
    void SetSustain(int Index, int Sustain);
    void SetReleaseMilliSeconds(int Index, float Release);

private:
    CConstNumSamplesGenerator<float> m_NumSamples;
    std::vector<CADSREnvelope<float>> m_Envelope;
};

#endif // ADSRENVELOPEBANKFILTER_H
