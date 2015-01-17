#include <algorithm>
#include "GranularFilter.h"
#include "GrainUtilities.h"

CGranularFilter::CGranularFilter()
 : m_PositionScale(8)
 , m_Grabber(1<<17)
 , m_ScaledPosition(0)
 , m_GrainBank(128)
 , m_GrainTrigger()
 , m_GrainSize(1<<12)
 , m_GrainSpeed(1<<CGrain<float>::SpeedScale)
 , m_GrainDensity(1<<11)
 , m_PositionSpeed(1<<m_PositionScale)
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
        if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
        {
            const float* DstBufferEnd = DstBuffer + NumFrames;
            while(DstBuffer<DstBufferEnd)
            {
                m_Grabber(*SrcBuffer);
                //*DstBuffer = m_Grabber.GetBuffer()[m_Position];

                *DstBuffer =
                m_GrainBank(m_Grabber.GetBuffer().data(), m_Grabber.GetSize(),
                            m_GrainTrigger(m_GrainDensity),
                            m_ScaledPosition>>m_PositionScale, m_GrainSize, m_GrainSpeed, 1.0f);


                m_ScaledPosition = grainutilities::UpdateCounter(m_ScaledPosition,
                                                                 m_PositionSpeed,
                                                                 m_Grabber.GetSize()<<m_PositionScale);

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

void CGranularFilter::SetSampleSize(int SizeShift)
{
    m_Grabber.SetSize(1<<SizeShift);
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

void CGranularFilter::SetGrainSize(int GrainSizeShift)
{
    m_GrainSize = 1<<GrainSizeShift;
}

void CGranularFilter::SetGrainSpeed(int GrainSpeed)
{
    m_GrainSpeed = GrainSpeed;//TODO scaled!!!
}

void CGranularFilter::SetGrainDensity(int GrainDensityShift)
{
    m_GrainDensity = 1<<GrainDensityShift;
}

void CGranularFilter::SetPositionSpeed(int PositionSpeed)
{
    m_PositionSpeed = PositionSpeed;
}
