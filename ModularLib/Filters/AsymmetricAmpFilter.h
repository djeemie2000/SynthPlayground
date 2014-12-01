#ifndef AsymmetricAmpFILTER_H
#define AsymmetricAmpFILTER_H

#include "AudioFilterI.h"
#include "AsymmetricAmp.h"

class CAsymmetricAmpFilter : public IAudioFilter
{
public:
    CAsymmetricAmpFilter();

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

    void SetAmpPos(float AmpPos);
    void SetAmpNeg(float AmpNeg);
    void SetAmpOffset(float Offset);
    void SetOffsetLockMode(bool Mode);

private:
    CAsymmetricAmp<float> m_Amp;
};

#endif // AsymmetricAmpFILTER_H
