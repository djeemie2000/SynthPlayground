#pragma once

#include "AudioFilterI.h"
#include "IntCombinedOperatorV2.h"
#include "FilterBuffers.h"

class CIntCombinedOperatorV2Filter : public IAudioFilter
{
public:
    CIntCombinedOperatorV2Filter(int SamplingFrequency);

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

    void SelectOperatorA(int Selected);
    void SelectOperatorB(int Selected);
    void SelectCombinor1(int Selected);
    void SetFrequencyMultiplierA(int Multiplier);
    void SetFrequencyMultiplierB(int Multiplier);
    void Sync();
    void SetOperatorACarrier(bool Carrier);

private:
    static const int OperatorScale = 12;
    static const int FrequencyScale = 10;
    static const int StrengthScale = 8;
    CFilterBuffers<float> m_Buffers;
    isl::CIntCombinedOperatorV2<OperatorScale, FrequencyScale, StrengthScale> m_CombinedOperator;
};
