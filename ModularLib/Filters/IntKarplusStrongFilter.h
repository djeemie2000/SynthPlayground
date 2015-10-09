#ifndef IntKarplusStrongFILTER_H
#define IntKarplusStrongFILTER_H

#include "AudioFilterI.h"
#include "IntKarplusStrong.h"
#include "FilterBuffers.h"

class CIntKarplusStrongFilter : public IAudioFilter
{
public:
    CIntKarplusStrongFilter(int SamplingFrequency);

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

    void SetPoles(int Poles);

private:
    static const int Scale = 12;
    static const int Capacity = 44100/10;
    static const int NumOperators = 12;
    isl::CKarplusStrong<int, Scale, Capacity, NumOperators> m_KarplusStrong;
    CFilterBuffers<float> m_Buffers;
};

#endif // IntKarplusStrongFILTER_H
