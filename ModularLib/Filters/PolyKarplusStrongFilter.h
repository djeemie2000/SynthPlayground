#ifndef PolyKarplusStrongFILTER_H
#define PolyKarplusStrongFILTER_H

#include "AudioFilterI.h"
#include "PolyKarplusStrong.h"
#include "FilterBuffers.h"

class CPolyKarplusStrongFilter : public IAudioFilter
{
public:
    CPolyKarplusStrongFilter(int SamplingFrequency);

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
    static const int Capacity = 44100/10;
    static const int NumOperators = 8;
    synthlib::CPolyKarplusStrong<float, Capacity, NumOperators> m_KarplusStrong;
    synthlib::CPolyKarplusStrong<float, Capacity, NumOperators> m_KarplusStrongExt;
    CFilterBuffers<float> m_Buffers;
};

#endif // PolyKarplusStrongFILTER_H
