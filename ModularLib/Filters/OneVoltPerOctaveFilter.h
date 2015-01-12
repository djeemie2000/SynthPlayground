#ifndef OneVoltPerOctaveFILTER_H
#define OneVoltPerOctaveFILTER_H

#include "AudioFilterI.h"
#include "OneVoltPerOctave.h"

class COneVoltPerOctaveFilter : public IAudioFilter
{
public:
    COneVoltPerOctaveFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  const std::vector<std::shared_ptr<IMidiHandler>> MidiHandlers,
                  int NumFrames,
                  std::uint32_t TimeStOneVoltPerOctave) override;

private:
    COneVoltPerOctave<float> m_OneVoltPerOctave;
};

#endif // OneVoltPerOctaveFILTER_H
