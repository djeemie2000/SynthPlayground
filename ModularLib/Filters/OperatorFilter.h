#ifndef OSCILLATORFILTER_H
#define OSCILLATORFILTER_H

#include "AudioFilterI.h"
#include "SelectableOperator.h"

class COperatorFilter : public IAudioFilter
{
public:
    COperatorFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    void Select(int Selection);

private:
    CSelectableOperator<float> m_Operator;
};

#endif // OSCILLATORFILTER_H
