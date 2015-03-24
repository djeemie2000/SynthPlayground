#include <algorithm>
#include "KarplusStrongFilter.h"

CKarplusStrongFilter::CKarplusStrongFilter(int SamplingFrequency)
 : m_KarplusStrong(SamplingFrequency, 10.0f)
{
}

std::vector<std::string> CKarplusStrongFilter::GetInputNames() const
{
    return { "Trigger", "Freq", "CutOff", "Excite" };
}

std::vector<std::string> CKarplusStrongFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CKarplusStrongFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CKarplusStrongFilter::GetMidiOutputNames() const
{
    return {};
}

int CKarplusStrongFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(OutBuffer)
    {
        const float* TriggerBuffer = static_cast<const float*>(SourceBuffers[0]);
        const float* FreqBuffer = static_cast<const float*>(SourceBuffers[1]);
        const float* CutoffBuffer = static_cast<const float*>(SourceBuffers[2]);
        const float* ExciteBuffer = static_cast<const float*>(SourceBuffers[3]);
        if(TriggerBuffer && CutoffBuffer && FreqBuffer && ExciteBuffer)
        {
            const float* InBufferEnd = TriggerBuffer+NumFrames;
            while(TriggerBuffer<InBufferEnd)
            {
                *OutBuffer = m_KarplusStrong(*TriggerBuffer, *FreqBuffer, *CutoffBuffer, *ExciteBuffer);
                ++TriggerBuffer;
                ++FreqBuffer;
                ++CutoffBuffer;
                ++ExciteBuffer;
                ++OutBuffer;
            }
        }
        else if(TriggerBuffer && CutoffBuffer && FreqBuffer)
        {
            const float* InBufferEnd = TriggerBuffer+NumFrames;
            while(TriggerBuffer<InBufferEnd)
            {
                *OutBuffer = m_KarplusStrong(*TriggerBuffer, *FreqBuffer, *CutoffBuffer);
                ++TriggerBuffer;
                ++FreqBuffer;
                ++CutoffBuffer;
                ++OutBuffer;
            }
        }
        // TODO default cutoff
        // TODO default freq??
        else
        {
            std::fill(OutBuffer, OutBuffer+NumFrames, 0.0f);
        }
    }

    return 0;
}

void CKarplusStrongFilter::SetPoles(int Poles)
{
    m_KarplusStrong.SetPoles(Poles);
}
