#ifndef LFOBANKFILTER_H
#define LFOBANKFILTER_H

#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"
#include "LFO.h"

class CLFOBankFilter : public IAudioFilter
{
public:
    CLFOBankFilter(int Size, int SamplingFrequency);

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

    void SetFrequency(int Index, float Frequency);
    void Select(int Index, int Selection);

private:
    std::vector<CLFO<float>> m_LFO;
};

#endif // LFOBANKFILTER_H
