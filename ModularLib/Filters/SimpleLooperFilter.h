#ifndef LooperFILTER_H
#define LooperFILTER_H

#include <vector>
#include "AudioFilterI.h"
#include "LoopRecorder.h"
#include "LoopPlayer.h"

class CSimpleLooperFilter : public IAudioFilter
{
public:
    CSimpleLooperFilter(int SamplingFrequency);

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
    CLoopRecorder<float> m_LoopRecorder;
    CLoopPlayer<float> m_LoopPlayer;
    std::vector<float> m_DefaultRecordGate;
    std::vector<float> m_DefaultIn;
    std::vector<float> m_DefaultOut;
};

#endif // LooperFILTER_H
