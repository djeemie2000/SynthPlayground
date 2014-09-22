#ifndef MODULATORFILTER_H
#define MODULATORFILTER_H

#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"

class CModulatorFilter : public IAudioFilter
{
public:
    CModulatorFilter(int Size);

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

    void SetModAmt(int Index, float ModAmt);
    void SetOffset(float Offset);
    void SetLimitMode(int Mode); // 0 = none, 1 = hard limit [-1,+1], 2 = hard limit [0,+1]

private:
    float               m_Offset;
    std::vector<float>  m_ModAmt;
    int                 m_LimitMode;
};

#endif // MODULATORFILTER_H
