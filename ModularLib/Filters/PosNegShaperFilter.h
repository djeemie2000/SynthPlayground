#ifndef POSNEGSHAPERFILTER_H
#define POSNEGSHAPERFILTER_H

#include "AudioFilterI.h"
#include "PosNegShaper.h"

class CPosNegShaperFilter : public IAudioFilter
{
public:
    CPosNegShaperFilter();

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

    void SetInvert(bool Invert);
    void SetInverterMode(int Mode);
    void SetDerectifierMode(int Mode);

private:
    bool                    m_Invert;
    CPosNegInverter<float> m_Inverter;
    CPosNegDerectifier<float> m_Derectifier;
};


#endif // POSNEGSHAPERFILTER_H
