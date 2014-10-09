#include "MidiLoggerFilter.h"
#include "LogMidiInputHandler.h"
#include "MidiRendererI.h"

CMidiLoggerFilter::CMidiLoggerFilter()
 : m_MidiHandler(new CLogMidiInputHandler())
{
}

std::vector<std::string> CMidiLoggerFilter::GetInputNames() const
{
    return {};
}

std::vector<std::string> CMidiLoggerFilter::GetOutputNames() const
{
    return {};
}


std::vector<std::string> CMidiLoggerFilter::GetMidiInputNames() const
{
    return {"MidiIn"};
}

std::vector<std::string> CMidiLoggerFilter::GetMidiOutputNames() const
{
    return {};
}

int CMidiLoggerFilter::OnProcess(const std::vector<void *> &/*SourceBuffers*/,
                               const std::vector<void *> &/*DestinationBuffers*/,
                               const std::vector<std::shared_ptr<IMidiRenderer> > MidiRenderers,
                               const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                               int /*NumFrames*/,
                               std::uint32_t /*TimeStamp*/)
{
    if(MidiRenderers[0])
    {
        MidiRenderers[0]->Accept(*m_MidiHandler);
    }

    return 0;//TODO
}
