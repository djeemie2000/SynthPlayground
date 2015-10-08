#include "IntKarplusStrongFilter.h"
#include "IntConversions.h"
#include "Trigger.h"

CIntKarplusStrongFilter::CIntKarplusStrongFilter(int /*SamplingFrequency*/)
 : m_KarplusStrong()
 , m_Buffers({0.0f, 110.0f, 0.9f, 0.9f},{0.0f})
{
}

std::vector<std::string> CIntKarplusStrongFilter::GetInputNames() const
{
    return { "Trigger", "Freq", "Damp", "Excitation" };
}

std::vector<std::string> CIntKarplusStrongFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CIntKarplusStrongFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CIntKarplusStrongFilter::GetMidiOutputNames() const
{
    return {};
}

int CIntKarplusStrongFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    CTriggerIn<float> TriggerIn;
    const int LPFMultiplier = (1<<isl::CKarplusStrong<int, Scale, Capacity>::LPFScale);

    const float* TriggerBuffer = m_Buffers.GetSourceBuffer(0);
    const float* FreqBuffer = m_Buffers.GetSourceBuffer(1);
    const float* DampBuffer = m_Buffers.GetSourceBuffer(2);
    const float* ExcitationBuffer = m_Buffers.GetSourceBuffer(3);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        if(TriggerIn.IsTriggerOn(*TriggerBuffer))
        {
            m_KarplusStrong.Excite((*ExcitationBuffer)*LPFMultiplier,
                                   (*FreqBuffer)*1000,
                                   (*DampBuffer)*LPFMultiplier);
        }
        *OutBuffer = isl::IntBipolarToFloatBipolar<int, float, Scale>(m_KarplusStrong());

        ++OutBuffer;
        ++ExcitationBuffer;
        ++DampBuffer;
        ++FreqBuffer;
        ++TriggerBuffer;
    }

    return 0;
}

void CIntKarplusStrongFilter::SetPoles(int /*Poles*/)
{
    //m_KarplusStrong.SetPoles(Poles);
}
