#include "RandomGateFilter.h"

CRandomGateFilter::CRandomGateFilter()
 : m_Gate()
{
}

std::vector<std::string> CRandomGateFilter::GetInputNames() const
{
    return { "OpenCentr", "CloseCentr" };
}

std::vector<std::string> CRandomGateFilter::GetOutputNames() const
{
    return { "Gate", "Trigger" };
}

std::vector<std::string> CRandomGateFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CRandomGateFilter::GetMidiOutputNames() const
{
    return {};
}

int CRandomGateFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
//    const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
    float* GateBuffer = static_cast<float*>(DestinationBuffers[0]);
    float* TriggerBuffer = static_cast<float*>(DestinationBuffers[1]);
    const float* GateOpenCenterBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* GateCloseCenterBuffer = static_cast<const float*>(SourceBuffers[1]);

    if(!GateOpenCenterBuffer || !GateCloseCenterBuffer)
    {
        int idx = 0;
        while(idx<NumFrames)
        {
            float Gate = m_Gate();
            float Trigger = m_Trigger(Gate);

            if(GateBuffer)
            {
                *(GateBuffer+idx) = Gate;
            }
            if(TriggerBuffer)
            {
                *(TriggerBuffer+idx) = Trigger;
            }

            ++idx;
        }
    }
    else
    {
        int idx = 0;
        while(idx<NumFrames)
        {
            float Gate = m_Gate(*GateOpenCenterBuffer, *GateCloseCenterBuffer);
            float Trigger = m_Trigger(Gate);

            if(GateBuffer)
            {
                *(GateBuffer+idx) = Gate;
            }
            if(TriggerBuffer)
            {
                *(TriggerBuffer+idx) = Trigger;
            }

            ++idx;
            ++GateOpenCenterBuffer;
            ++GateCloseCenterBuffer;
        }
    }
    return 0;
}

void CRandomGateFilter::SetGateOpenScale(int Scale)
{
    m_Gate.SetGateOpenScale(Scale);
}

void CRandomGateFilter::SetGateCloseScale(int Scale)
{
    m_Gate.SetGateCloseScale(Scale);
}

void CRandomGateFilter::SetGateOpenCenter(float Center)
{
    m_Gate.SetGateOpenCenter(Center);
}

void CRandomGateFilter::SetGateCloseCenter(float Center)
{
    m_Gate.SetGateCloseCenter(Center);
}

void CRandomGateFilter::SetGateOpenVariation(float Variation)
{
    m_Gate.SetGateOpenVariation(Variation);
}

void CRandomGateFilter::SetGateCloseVariation(float Variation)
{
    m_Gate.SetGateCloseVariation(Variation);
}
