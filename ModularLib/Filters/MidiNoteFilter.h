#ifndef MIDINOTEFILTER_H
#define MIDINOTEFILTER_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include "AudioFilterI.h"
#include "MidiInputHandlerI.h"

class CTriggerMidiNoteHandler;

class CMidiNoteFilter : public IAudioFilter
{
public:
    CMidiNoteFilter();

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

    void OnMidiPanic();

private:
    std::shared_ptr<CTriggerMidiNoteHandler> m_MidiNoteHandler; //!< does the actual work
    std::shared_ptr<IMidiHandler> m_NoteCountHandler; //!< added to avoid issue with multiple simultanious notes
};

#endif // MIDINOTEFILTER_H
