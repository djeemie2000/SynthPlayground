#ifndef RandomGateFILTER_H
#define RandomGateFILTER_H

#include "AudioFilterI.h"
#include "RandomGate.h"

class CRandomGateFilter : public IAudioFilter
{
public:
    CRandomGateFilter();

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

    void SetGateOpenScale(int Scale);
    void SetGateCloseScale(int Scale);
    void SetGateOpenCenter(float Center);
    void SetGateCloseCenter(float Center);
    void SetGateOpenVariation(float Variation);
    void SetGateCloseVariation(float Variation);

private:
    CRandomGate<float> m_Gate;
};

#endif // RandomGateFILTER_H
