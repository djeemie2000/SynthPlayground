#include "PolyKarplusStrongFilter.h"
#include "Trigger.h"

CPolyKarplusStrongFilter::CPolyKarplusStrongFilter(int SamplingFrequency)
 : m_KarplusStrong()
 , m_KarplusStrongExt()
 , m_Buffers({0.0f, 110.0f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f, 0.0f})
{
    m_KarplusStrong.SetSamplingFrequency(SamplingFrequency);
}

std::vector<std::string> CPolyKarplusStrongFilter::GetInputNames() const
{
    return { "Trigger", "Freq", "Damp", "Excitation", "Attack", "Pan", "Noise", "In" };
}

std::vector<std::string> CPolyKarplusStrongFilter::GetOutputNames() const
{
    return { "Out", "OutR", "OutExtL", "OutExtR" };
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
    const float* PanBuffer = m_Buffers.GetSourceBuffer(5);
    const float* NoiseBuffer = m_Buffers.GetSourceBuffer(6);
    const float* ExtInBuffer = m_Buffers.GetSourceBuffer(7);
    float* OutLBuffer = m_Buffers.GetDestinationBuffer(0);
    float* OutRBuffer = m_Buffers.GetDestinationBuffer(1);
    float* OutExtLBuffer = m_Buffers.GetDestinationBuffer(2);
    float* OutExtRBuffer = m_Buffers.GetDestinationBuffer(3);

    const float* OutLBufferEnd = OutLBuffer + NumFrames;
    while(OutLBuffer<OutLBufferEnd)
    {
        if(TriggerIn.IsTriggerOn(*TriggerBuffer))
        {
            int AttackMilliSeconds = (*AttackBuffer)*1000;
            m_KarplusStrong.Excite(*ExcitationBuffer,
                                   *FreqBuffer,
                                   *DampBuffer,
                                   AttackMilliSeconds,
                                   *PanBuffer);
            m_KarplusStrongExt.Excite(*ExcitationBuffer,
                                   *FreqBuffer,
                                   *DampBuffer,
                                   AttackMilliSeconds,
                                   *PanBuffer);
        }
        m_KarplusStrong(*NoiseBuffer, *OutLBuffer, *OutRBuffer);
        m_KarplusStrongExt.Process(*ExtInBuffer, *NoiseBuffer, *OutExtLBuffer, *OutExtRBuffer);

        ++OutLBuffer;
        ++OutRBuffer;
        ++OutExtLBuffer;
        ++OutExtRBuffer;
        ++ExcitationBuffer;
        ++DampBuffer;
        ++FreqBuffer;
        ++TriggerBuffer;
        ++AttackBuffer;
        ++PanBuffer;
        ++NoiseBuffer;
        ++ExtInBuffer;
    }

    return 0;
}

void CPolyKarplusStrongFilter::SetPoles(int Poles)
{
    m_KarplusStrong.SetNumOperators(Poles);
}
