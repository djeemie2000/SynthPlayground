#include "MidiOctaveGateFilter.h"
#include "NoteActiveMidiHandler.h"
#include "MidiRendererI.h"

namespace
{

static const int NumGates = 12;

}

CMidiOctaveGateFilter::CMidiOctaveGateFilter()
 : m_MidiNoteHandler(new CNoteActiveMidiHandler())
 , m_Octave(0)
{
}

std::vector<std::string> CMidiOctaveGateFilter::GetInputNames() const
{
    return {};
}

std::vector<std::string> CMidiOctaveGateFilter::GetOutputNames() const
{
    std::vector<std::string> OutputNames;
    for(int Gate = 0; Gate<NumGates; ++Gate)
    {
        OutputNames.push_back("Gate"+std::to_string(Gate));
    }
    return OutputNames;
}


std::vector<std::string> CMidiOctaveGateFilter::GetMidiInputNames() const
{
    return {"MidiIn"};
}

std::vector<std::string> CMidiOctaveGateFilter::GetMidiOutputNames() const
{
    return {};
}

int CMidiOctaveGateFilter::OnProcess(const std::vector<void *> &/*SourceBuffers*/,
                               const std::vector<void *> &DestinationBuffers,
                               const std::vector<std::shared_ptr<IMidiRenderer> > MidiRenderers,
                               const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                               int NumFrames,
                               std::uint32_t /*TimeStamp*/)
{
    if(MidiRenderers[0])
    {
        MidiRenderers[0]->Accept(*m_MidiNoteHandler);
    }
    for(int Gate = 0; Gate<NumGates; ++Gate)
    {
        if(DestinationBuffers[Gate])
        {
            int MidiNote = (1+m_Octave)*12+Gate;// C0 is midi note 12, 12 notes per octave cfr MidiNoteConverter
            float GateValue = m_MidiNoteHandler->GetNoteActive(MidiNote) ? 1.0f : 0.0f;
            float* GateBuffer = static_cast<float*>(DestinationBuffers[Gate]);
            std::fill(GateBuffer, GateBuffer + NumFrames, GateValue);
        }
    }

    return 0;
}

void CMidiOctaveGateFilter::SetOctave(int Octave)
{
    if(-1<=Octave && Octave<=8)
    {
        m_Octave = Octave;
    }
}
