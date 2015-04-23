#ifndef ToggleGateFILTER_H
#define ToggleGateFILTER_H

#include "AudioFilterI.h"
#include "ToggleGate.h"
#include "Trigger.h"

class CToggleGateFilter : public IAudioFilter
{
public:
    CToggleGateFilter();

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
    CToggleGate<float> m_ToggleGate;
    CGateToTrigger<float> m_GateToTrigger;
};

#endif // ToggleGateFILTER_H
