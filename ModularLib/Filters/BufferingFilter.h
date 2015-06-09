#ifndef BufferingFILTER_H
#define BufferingFILTER_H

#include <vector>
#include <string>
#include <memory>
#include "AudioFilterI.h"
#include "simplereadwritebuffer.h"

class CBufferingFilter : public IAudioFilter
{
public:
    CBufferingFilter(int SamplingFrequency, int CapacityMilliSeconds, const std::vector<std::string>& InputNames);

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

    int ReadBuffer(int idxBuffer, float* Destination, int Size);

private:
    std::vector<std::string> m_InputNames;
    std::vector< std::unique_ptr<CSimpleReadWriteBuffer<float>> > m_Buffers;
};

#endif // BufferingFILTER_H
