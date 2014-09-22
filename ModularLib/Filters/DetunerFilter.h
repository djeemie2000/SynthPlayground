#ifndef DetunerFILTER_H
#define DetunerFILTER_H

#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"
#include "Detuner.h"

class CDetunerFilter : public IAudioFilter
{
public:
    CDetunerFilter(int Size);

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    void SetDetune(int Index, float Detune);
    void SetOctaveShift(int Index, int OctaveShift);

private:
    std::vector<CDetuner<float>> m_Detuner;
};

#endif // DetunerFILTER_H
