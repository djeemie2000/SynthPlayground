#pragma once

#include "AudioFilterI.h"
#include "IntCombinedOperator.h"
#include "FilterBuffers.h"

class CIntCombinedOperatorFilter : public IAudioFilter
{
public:
    CIntCombinedOperatorFilter(int SamplingFrequency);

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
    void SelectOperatorC(int Selected);
    void SelectCombinor2(int Selected);

private:
    static const int Scale = 12;
    CFilterBuffers<float> m_Buffers;
    isl::CIntCombinedOperator<Scale> m_CombinedOperator;
};
