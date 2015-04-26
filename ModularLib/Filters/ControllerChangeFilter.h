#ifndef ControllerChangeFILTER_H
#define ControllerChangeFILTER_H

#include <vector>
#include "AudioFilterI.h"
#include "ControllerChange.h"

class CControllerChangeFilter : public IAudioFilter
{
public:
    CControllerChangeFilter(int SamplingFrequency);

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
    const float m_DefaultRateValue;
    CControllerChange<float> m_ControllerChange;
    std::vector<float> m_DefaultRate;
    std::vector<float> m_DefaultIncr;
    std::vector<float> m_DefaultDecr;
};

#endif // ControllerChangeFILTER_H
