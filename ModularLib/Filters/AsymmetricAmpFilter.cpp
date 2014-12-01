#include <algorithm>
#include "AsymmetricAmpFilter.h"

CAsymmetricAmpFilter::CAsymmetricAmpFilter()
 : m_Amp()
{
}

std::vector<std::string> CAsymmetricAmpFilter::GetInputNames() const
{
    return { "In" };
}

std::vector<std::string> CAsymmetricAmpFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CAsymmetricAmpFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CAsymmetricAmpFilter::GetMidiOutputNames() const
{
    return {};
}

int CAsymmetricAmpFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(InBuffer && OutBuffer)
    {
        std::transform(InBuffer, InBuffer+NumFrames, OutBuffer, m_Amp);// -> uses a copy of m_Amp?
//        const float* InBufferEnd = InBuffer+NumFrames;
//        while(InBuffer<InBufferEnd)
//        {
//            *OutBuffer = m_Amp(*InBuffer);
//            ++InBuffer;
//            ++OutBuffer;
//        }
    }
    else if(OutBuffer)
    {
        std::fill(OutBuffer, OutBuffer+NumFrames, 0.0f);
    }

    return 0;
}

void CAsymmetricAmpFilter::SetAmpPos(float AmpPos)
{
    m_Amp.SetAmpPos(AmpPos);
}

void CAsymmetricAmpFilter::SetAmpNeg(float AmpNeg)
{
    m_Amp.SetAmpNeg(AmpNeg);
}

void CAsymmetricAmpFilter::SetAmpOffset(float Offset)
{
    m_Amp.SetOffset(Offset);
}

void CAsymmetricAmpFilter::SetOffsetLockMode(bool Mode)
{
    m_Amp.SetOffsetLockMode(Mode);
}
