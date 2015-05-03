#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include "AudioFilterI.h"
#include "MidiHandlerI.h"

class CNoteActiveMidiHandler;

class CMidiOctaveGateFilter : public IAudioFilter
{
public:
    CMidiOctaveGateFilter();

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

    void SetOctave(int Octave);

private:
    std::shared_ptr<CNoteActiveMidiHandler> m_MidiNoteHandler; //!< does the actual work
    int m_Octave;
};
