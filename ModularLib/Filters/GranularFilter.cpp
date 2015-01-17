#include <algorithm>
#include "GranularFilter.h"
#include "GrainUtilities.h"

CGranularFilter::CGranularFilter()
 : m_Grabber(1<<16)
 , m_Cntr(0)
{
}

std::vector<std::string> CGranularFilter::GetInputNames() const
{
    return {"In"};
}

std::vector<std::string> CGranularFilter::GetOutputNames() const
{
    return {"Out"};
}

std::vector<std::string> CGranularFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CGranularFilter::GetMidiOutputNames() const
{
    return {};
}

int CGranularFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    if(const float* SrcBuffer = static_cast<const float*>(SourceBuffers[0]))
    {
        // ??? what if sample size < NumFrames ???
//        const float* SrcBufferEnd = SrcBuffer + NumFrames;
//        while(SrcBuffer<SrcBufferEnd)
//        {
//            m_Grabber(*SrcBuffer);
//            ++SrcBuffer;
//        }

        if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
        {
            const float* DstBufferEnd = DstBuffer + NumFrames;
            while(DstBuffer<DstBufferEnd)
            {
                m_Grabber(*SrcBuffer);
                *DstBuffer = m_Grabber.GetBuffer()[m_Cntr];
                m_Cntr = grainutilities::UpdateCounter(m_Cntr, 1, m_Grabber.GetSize());

                ++SrcBuffer;
                ++DstBuffer;
            }
        }
        else
        {
            const float* SrcBufferEnd = SrcBuffer + NumFrames;
            while(SrcBuffer<SrcBufferEnd)
            {
                m_Grabber(*SrcBuffer);
                ++SrcBuffer;
            }
        }
    }
    else if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
    {
        std::fill(DstBuffer, DstBuffer + NumFrames, 0.0f);
    }

    return 0;
}

void CGranularFilter::SetSampleSize(int Size)
{
    m_Grabber.SetSize(Size);
}

void CGranularFilter::SetSampleGrab(bool Grab)
{
    if(Grab)
    {
        m_Grabber.Grab();
    }
}

int CGranularFilter::GetSampleCapacity() const
{
    return m_Grabber.GetCapacity();
}
