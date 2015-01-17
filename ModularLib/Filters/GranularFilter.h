#ifndef GranularFILTER_H
#define GranularFILTER_H

#include <cstdint>
#include <string>
#include <vector>
#include "AudioFilterI.h"
#include "BufferGrabber.h"

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

    void SetSampleSize(int Size);
    void SetSampleGrab(bool Grab);
    int GetSampleCapacity() const;

private:
    CBufferGrabber<float> m_Grabber;
    int m_Cntr;
};

#endif // GranularFILTER_H
