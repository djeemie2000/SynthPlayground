#ifndef GlitchFILTER_H
#define GlitchFILTER_H

#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"
#include "GlitchOperator.h"

class CGlitchFilter : public IAudioFilter
{
public:
    CGlitchFilter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    std::vector<std::string> GetMidiOutputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    void SetOctaveShift(int OctaveShift);
    void SetGrainSizeIn(int GrainSize);
    void SetGrainSizeOut(int GrainSize);

private:
    CGlitchOperator<float> m_Glitch;
    int m_GrainSizeOut;
};

#endif // GlitchFILTER_H
