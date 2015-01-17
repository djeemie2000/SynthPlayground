#ifndef GranularFILTER_H
#define GranularFILTER_H

#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"
#include "BufferGrabber.h"
#include "GrainBank.h"
#include "GrainTrigger.h"

class CGranularFilter : public IAudioFilter
{
public:
    CGranularFilter();

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

    void SetSampleSize(int SizeShift);
    void SetSampleGrab(bool Grab);
    int GetSampleCapacity() const;

    void SetGrainSize(int GrainSizeShift);
    void SetGrainSpeed(int GrainSpeed);
    void SetGrainDensity(int GrainDensityShift);

    void SetPositionSpeed(int PositionSpeed);

private:
    const int m_PositionScale;
    CBufferGrabber<float> m_Grabber;
    int m_ScaledPosition;
    CGrainBank<float>   m_GrainBank;
    CDensityGrainTrigger m_GrainTrigger;
    int m_GrainSize;
    int m_GrainSpeed;
    int m_GrainDensity;
    int m_PositionSpeed;
};

#endif // GranularFILTER_H
