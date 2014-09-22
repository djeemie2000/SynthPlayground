#ifndef MultiStageWaveFolderFILTER_H
#define MultiStageWaveFolderFILTER_H

#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"
#include "WaveFolder2.h"

class CMultiStageWaveFolderFilter : public IAudioFilter
{
public:
    CMultiStageWaveFolderFilter();

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

    void SetNumStages(int NumStages);

private:
    CMultiStageWaveFolder<float> m_MultiStageWaveFolder;
};

#endif // MultiStageWaveFolderFILTER_H
