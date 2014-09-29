#include <algorithm>
#include "MidiControllerBankFilter.h"
#include "MidiRendererI.h"
#include "MultiMidiHandler.h"

CMidiControllerBankFilter::CMidiControllerBankFilter(int Size)
    : m_Handler(Size)
    , m_MultiHandler()
{
    std::shared_ptr<CMultiMidiHandler> Multi(new CMultiMidiHandler());
    for(auto& Handler : m_Handler)
    {
        Handler.reset(new CMidiControllerValueHandler());
        Multi->AddHandler(Handler);
    }
    m_MultiHandler = Multi;
}

std::vector<std::string> CMidiControllerBankFilter::GetInputNames() const
{
    return {};
}

std::vector<std::string> CMidiControllerBankFilter::GetOutputNames() const
{
    std::vector<std::string> Names;
    for(std::size_t idx = 0; idx<m_Handler.size(); ++idx)
    {
        Names.push_back("Contr"+std::to_string(idx));
    }
    return Names;
}

std::vector<std::string> CMidiControllerBankFilter::GetMidiInputNames() const
{
    return {"MidiIn"};
}

std::vector<std::string> CMidiControllerBankFilter::GetMidiOutputNames() const
{
    return {};
}

int CMidiControllerBankFilter::OnProcess(const std::vector<void *> &/*SourceBuffers*/,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                            const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    // TODO multiplexer to handle multiple parameters
    for(std::size_t idx = 0; idx<m_Handler.size(); ++idx)
    {
        m_Handler[idx]->OnStart((float*)DestinationBuffers[idx], NumFrames);
    }
    if(MidiRenderers[0])
    {
        MidiRenderers[0]->Accept(*m_MultiHandler);
    }
    for(std::size_t idx = 0; idx<m_Handler.size(); ++idx)
    {
        m_Handler[idx]->OnFinish();
    }

    return 0;
}

void CMidiControllerBankFilter::SetParam(int Index, int Param)
{
    m_Handler[Index]->SetParameter(Param);
}

void CMidiControllerBankFilter::SetMin(int Index, float Min)
{
    m_Handler[Index]->SetMin(Min);
}

void CMidiControllerBankFilter::SetMax(int Index, float Max)
{
    m_Handler[Index]->SetMax(Max);
}
