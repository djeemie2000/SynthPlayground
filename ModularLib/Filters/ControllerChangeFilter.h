#ifndef ControllerChangeFILTER_H
#define ControllerChangeFILTER_H

#include "AudioFilterI.h"
#include "ControllerChange.h"

class CControllerChangeFilter : public IAudioFilter
{
public:
    CControllerChangeFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  const std::vector<std::shared_ptr<IMidiHandler>> MidiHandlers,
                  int NumFrames,
                  std::uint32_t TimeStControllerChange) override;

private:
    CControllerChange<float> m_ControllerChange;
};

#endif // ControllerChangeFILTER_H
