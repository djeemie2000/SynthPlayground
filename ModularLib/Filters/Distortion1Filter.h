#ifndef Distortion1FILTER_H
#define Distortion1FILTER_H

#include "AudioFilterI.h"
#include "PowerLawDistortion.h"

class CDistortion1Filter : public IAudioFilter
{
public:
    CDistortion1Filter();

    std::vector<std::string> GetInputNames() const override;
    std::vector<std::string> GetOutputNames() const override;
    std::vector<std::string> GetMidiInputNames() const override;
    int OnProcess(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                  int NumFrames,
                  std::uint32_t TimeStamp) override;

    void SetDrive(float Drive);

private:
    CPowerLawDistortion<float> m_Distortion;
};

#endif // Distortion1FILTER_H
