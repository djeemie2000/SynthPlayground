#include <algorithm>
#include "ToggleGateFilter.h"
#include "ToggleGate.h"

CToggleGateFilter::CToggleGateFilter()
 : m_ToggleGate()
 , m_GateToTrigger()
{
}

std::vector<std::string> CToggleGateFilter::GetInputNames() const
{
    return { "Toggle" };
}

std::vector<std::string> CToggleGateFilter::GetOutputNames() const
{
    return { "Gate", "Trigger" };
}

std::vector<std::string> CToggleGateFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CToggleGateFilter::GetMidiOutputNames() const
{
    return {};
}

int CToggleGateFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    float* GateOutBuffer = static_cast<float*>(DestinationBuffers[0]);
    float* TriggerOutBuffer = static_cast<float*>(DestinationBuffers[1]);

    const float* ToggleBuffer = static_cast<const float*>(SourceBuffers[0]);
    if(ToggleBuffer && GateOutBuffer && TriggerOutBuffer)
    {
        const float* ToggleBufferEnd = ToggleBuffer + NumFrames;
        while(ToggleBuffer<ToggleBufferEnd)
        {
            *GateOutBuffer = m_ToggleGate(*ToggleBuffer);
            *TriggerOutBuffer = m_GateToTrigger(*GateOutBuffer);
            ++ToggleBuffer;
            ++GateOutBuffer;
            ++TriggerOutBuffer;
        }
    }
    else if(ToggleBuffer && GateOutBuffer)
    {
        const float* ToggleBufferEnd = ToggleBuffer + NumFrames;
        while(ToggleBuffer<ToggleBufferEnd)
        {
            *GateOutBuffer = m_ToggleGate(*ToggleBuffer);
            m_GateToTrigger(*GateOutBuffer);
            ++ToggleBuffer;
            ++GateOutBuffer;
        }
    }
    else if(ToggleBuffer && TriggerOutBuffer)
    {
        const float* ToggleBufferEnd = ToggleBuffer + NumFrames;
        while(ToggleBuffer<ToggleBufferEnd)
        {
            *TriggerOutBuffer = m_GateToTrigger(m_ToggleGate(*ToggleBuffer));
            ++ToggleBuffer;
            ++TriggerOutBuffer;
        }
    }
    else if(GateOutBuffer)
    {
        std::fill(GateOutBuffer, GateOutBuffer+NumFrames, 0.0f);
    }

    return 0;
}
