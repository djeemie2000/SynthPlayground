#ifndef ScalerFILTER_H
#define ScalerFILTER_H

#include "AudioFilterI.h"
#include "Scaler.h"

class CScalerFilter : public IAudioFilter
{
public:
    CScalerFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  const std::vector<std::shared_ptr<IMidiHandler>> MidiHandlers,
                  int NumFrames,
                  std::uint32_t TimeStScaler) override;

private:
    CScaler<float> m_Scaler;
};

#endif // ScalerFILTER_H
