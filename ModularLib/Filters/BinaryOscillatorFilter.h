#ifndef BinaryOscillatorFILTER_H
#define BinaryOscillatorFILTER_H

#include "AudioFilterI.h"
#include "BinaryOscillator.h"

class CBinaryOscillatorFilter : public IAudioFilter
{
public:
    CBinaryOscillatorFilter();

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
    CBinaryOscillator<float> m_BinaryOscillator;
};

#endif // BinaryOscillatorFILTER_H
