#include "MidiNoteFilter.h"
#include "notecountmidiinputhandler.h"
#include "TriggerMidiNoteHandler.h"
#include "MidiRendererI.h"

CMidiNoteFilter::CMidiNoteFilter()
 : m_MidiNoteHandler(new CTriggerMidiNoteHandler())
 , m_NoteCountHandler(new CNoteCountMidiInputHandler(m_MidiNoteHandler))
{
}

std::vector<std::string> CMidiNoteFilter::GetInputNames() const
{
    return {};
}

std::vector<std::string> CMidiNoteFilter::GetOutputNames() const
{
    return {"Freq", "Trigger"};
}


std::vector<std::string> CMidiNoteFilter::GetMidiInputNames() const
{
    return {"MidiIn"};
}

std::vector<std::string> CMidiNoteFilter::GetMidiOutputNames() const
{
    return {};
}

int CMidiNoteFilter::OnProcess(const std::vector<void *> &/*SourceBuffers*/,
                               const std::vector<void *> &DestinationBuffers,
                               const std::vector<std::shared_ptr<IMidiRenderer> > MidiRenderers,
                               const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                               int NumFrames,
                               std::uint32_t /*TimeStamp*/)
{
    if(MidiRenderers[0])
    {
        float* FreqBuffer = (float*)(DestinationBuffers[0]);
        float* TriggerBuffer = (float*)(DestinationBuffers[1]);
        m_MidiNoteHandler->OnStart(FreqBuffer, TriggerBuffer, NumFrames);
        MidiRenderers[0]->Accept(*m_NoteCountHandler);
        m_MidiNoteHandler->OnFinish();
    }

    return 0;//TODO
}
