#pragma once

#include "AudioFilterI.h"
#include "IntWaveFolder.h"
#include "FilterBuffers.h"

class CIntWaveFolderFilter : public IAudioFilter
{
public:
    CIntWaveFolderFilter();

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
    static const int ValueScale = 12;
    static const int FoldScale = 8;
    isl::CWaveFolder<int, ValueScale, FoldScale> m_WaveFolder;
    CFilterBuffers<float> m_Buffers;
};
