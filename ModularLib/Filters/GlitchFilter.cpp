#include <algorithm>
#include "GlitchFilter.h"

CGlitchFilter::CGlitchFilter()
 : m_Glitch()
 , m_GrainSizeOut(6)
{
}

std::vector<std::string> CGlitchFilter::GetInputNames() const
{
    return {"In"};
}

std::vector<std::string> CGlitchFilter::GetOutputNames() const
{
    return {"Out"};
}

std::vector<std::string> CGlitchFilter::GetMidiInputNames() const
{
    return {};
}

int CGlitchFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    if(const float* SrcBuffer = static_cast<const float*>(SourceBuffers[0]))
    {        
        if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
        {
            int GrainSizeOut = 1 << m_GrainSizeOut;
            int DstOffset = 0;
            while(DstOffset<NumFrames)
            {
                m_Glitch.Process(SrcBuffer+DstOffset, DstBuffer+DstOffset, GrainSizeOut);
                DstOffset += GrainSizeOut;
            }
        }
    }
    else if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
    {
        std::fill(DstBuffer, DstBuffer + NumFrames, 0.0f);
    }

    return 0;
}

void CGlitchFilter::SetOctaveShift(int OctaveShift)
{
    m_Glitch.SetGrainSpeed(OctaveShift);
}

void CGlitchFilter::SetGrainSizeIn(int GrainSize)
{
    m_Glitch.SetGrainSize(GrainSize);
}

void CGlitchFilter::SetGrainSizeOut(int GrainSize)
{
    m_GrainSizeOut = GrainSize;
}
