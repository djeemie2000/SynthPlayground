#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include "AudioFilterI.h"
#include "MidiControllerValueHandler.h"

class CMidiControllerBankFilter : public IAudioFilter
{
public:
    CMidiControllerBankFilter(int Size);

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

    void SetParam(int Index, int Param);
    void SetMin(int Index, float Min);
    void SetMax(int Index, float Max);

private:
    std::vector<std::shared_ptr<CMidiControllerValueHandler>> m_Handler;
    std::shared_ptr<IMidiHandler> m_MultiHandler;
};
