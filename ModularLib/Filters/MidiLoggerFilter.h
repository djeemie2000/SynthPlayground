#ifndef MidiLoggerFILTER_H
#define MidiLoggerFILTER_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include "AudioFilterI.h"

class IMidiHandler;

class CMidiLoggerFilter : public IAudioFilter
{
public:
    CMidiLoggerFilter();

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
    std::shared_ptr<IMidiHandler> m_MidiHandler; //!< does the actual work
};

#endif // MidiLoggerFILTER_H
