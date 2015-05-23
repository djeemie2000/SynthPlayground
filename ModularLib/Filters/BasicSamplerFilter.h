#ifndef BasicSamplerFILTER_H
#define BasicSamplerFILTER_H

#include <vector>
#include <string>
#include "AudioFilterI.h"
#include "WavFileReader.h"
#include "LoopPlayer.h"
#include "Trigger.h"

class CBasicSamplerFilter : public IAudioFilter
{
public:
    CBasicSamplerFilter(int SamplingFrequency);

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

    void OnLoad(const std::string& Path);

private:
    const float m_SamplingFrequency;
    CWavFileReader m_Reader;
    CPlayerIndex<float> m_PlayerIndex;
    CBasicSingleShotPlayer<float> m_PlayerLeft;
    CBasicSingleShotPlayer<float> m_PlayerRight;
    CGateToTrigger<float> m_GateToTrigger;
    std::vector<float> m_DefaultOutLeft;
    std::vector<float> m_DefaultOutRight;
    std::vector<float> m_DefaultGateOut;
};

#endif // BasicSamplerFILTER_H
