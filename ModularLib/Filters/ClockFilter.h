#ifndef ClockFILTER_H
#define ClockFILTER_H

#include "AudioFilterI.h"
#include "ClockPulse.h"

class CClockFilter : public IAudioFilter
{
public:
    CClockFilter(int SamplingFrequency);

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

    void SetBeatsPerMinute(int Bpm);
    void SetBeatsPerBar(int Bpb);
    void SetSubDivision(int SubDivision);

private:
    CClockPulseOut<float>   m_Clock;
};

#endif // ClockFILTER_H
