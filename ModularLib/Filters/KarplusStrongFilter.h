#ifndef KarplusStrongFILTER_H
#define KarplusStrongFILTER_H

#include "AudioFilterI.h"
#include "karplusstrong.h"

class CKarplusStrongFilter : public IAudioFilter
{
public:
    CKarplusStrongFilter(int SamplingFrequency);

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

private:
    CKarplusStrong<float> m_KarplusStrong;
};

#endif // KarplusStrongFILTER_H
