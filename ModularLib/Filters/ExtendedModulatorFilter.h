#ifndef EXTENDEDMODULATORFILTER_H
#define EXTENDEDMODULATORFILTER_H

#include <cstdint>
#include "AudioFilterI.h"

class CExtendedModulatorFilter : public IAudioFilter
{
public:
    CExtendedModulatorFilter(int Size);

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
    int m_Size;
};

#endif // EXTENDEDMODULATORFILTER_H
