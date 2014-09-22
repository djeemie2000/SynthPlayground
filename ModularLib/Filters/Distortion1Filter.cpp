#include <algorithm>
#include "Distortion1Filter.h"

CDistortion1Filter::CDistortion1Filter()
 : m_Distortion()
{
}

std::vector<std::string> CDistortion1Filter::GetInputNames() const
{
    return { "In", "Drive" };
}

std::vector<std::string> CDistortion1Filter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CDistortion1Filter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CDistortion1Filter::GetMidiOutputNames() const
{
    return {};
}

int CDistortion1Filter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* DriveBuffer = static_cast<const float*>(SourceBuffers[1]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(InBuffer && DriveBuffer && OutBuffer)
    {
        //std::transform(InBuffer, InBuffer+NumFrames, CutoffBuffer, OutBuffer, m_Distortion1ilter); -> uses a copy of m_Distortion?
        const float* InBufferEnd = InBuffer+NumFrames;
        while(InBuffer<InBufferEnd)
        {
            *OutBuffer = m_Distortion(*InBuffer, *DriveBuffer);
            ++InBuffer;
            ++DriveBuffer;
            ++OutBuffer;
        }
    }
    else if(InBuffer && OutBuffer)
    {
        const float* InBufferEnd = InBuffer+NumFrames;
        while(InBuffer<InBufferEnd)
        {
            *OutBuffer = m_Distortion(*InBuffer);
            ++InBuffer;
            ++OutBuffer;
        }
    }
    else if(OutBuffer)
    {
        std::fill(OutBuffer, OutBuffer + NumFrames, 0.0f);
    }

    return 0;
}

void CDistortion1Filter::SetDrive(float Drive)
{
    m_Distortion.SetDrive(Drive);
}
