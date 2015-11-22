#include "PolyKarplusStrongFilter.h"
#include "Trigger.h"

CPolyKarplusStrongFilter::CPolyKarplusStrongFilter(int SamplingFrequency)
 : m_KarplusStrong()
 , m_Buffers({0.0f, 110.0f, 0.9f, 0.9f, 0.0f},{0.0f})
{
    m_KarplusStrong.SetSamplingFrequency(SamplingFrequency);
}

std::vector<std::string> CPolyKarplusStrongFilter::GetInputNames() const
{
    return { "Trigger", "Freq", "Damp", "Excitation", "Attack" };
}

std::vector<std::string> CPolyKarplusStrongFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CPolyKarplusStrongFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CPolyKarplusStrongFilter::GetMidiOutputNames() const
{
    return {};
}

int CPolyKarplusStrongFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    CTriggerIn<float> TriggerIn;

    const float* TriggerBuffer = m_Buffers.GetSourceBuffer(0);
    const float* FreqBuffer = m_Buffers.GetSourceBuffer(1);
    const float* DampBuffer = m_Buffers.GetSourceBuffer(2);
    const float* ExcitationBuffer = m_Buffers.GetSourceBuffer(3);
    const float* AttackBuffer = m_Buffers.GetSourceBuffer(4);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        if(TriggerIn.IsTriggerOn(*TriggerBuffer))
        {
            int AttackMilliSeconds = (*AttackBuffer)*1000;
            m_KarplusStrong.Excite(*ExcitationBuffer,
                                   *FreqBuffer,
                                   *DampBuffer,
                                   AttackMilliSeconds);
        }
        *OutBuffer = m_KarplusStrong();

        ++OutBuffer;
        ++ExcitationBuffer;
        ++DampBuffer;
        ++FreqBuffer;
        ++TriggerBuffer;
        ++AttackBuffer;
    }

    return 0;
}

void CPolyKarplusStrongFilter::SetPoles(int Poles)
{
    m_KarplusStrong.SetNumOperators(Poles);
}
