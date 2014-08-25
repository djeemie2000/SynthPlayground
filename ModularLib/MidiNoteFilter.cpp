#include "MidiNoteFilter.h"

CMidiNoteFilter::CMidiNoteFilter()
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

int CMidiNoteFilter::OnProcess(const std::vector<void *> &/*SourceBuffers*/,
                               const std::vector<void *> &DestinationBuffers,
                               const std::vector<std::shared_ptr<IMidiRenderer> > MidiRenderers,
                               int NumFrames,
                               std::uint32_t TimeStamp)
{
    //TODO
}
