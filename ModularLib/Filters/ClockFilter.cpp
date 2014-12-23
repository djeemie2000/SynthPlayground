#include "ClockFilter.h"

CClockFilter::CClockFilter(int SamplingFrequency)
    : m_Clock(SamplingFrequency)
{
    m_Clock.SetBeatsPerMinute(120);
    m_Clock.SetBarsPerBeat(1);
    m_Clock.SetSubDivision(128);
}

std::vector<std::string> CClockFilter::GetInputNames() const
{
    return {};
}

std::vector<std::string> CClockFilter::GetOutputNames() const
{
    return {"Clock"};
}

std::vector<std::string> CClockFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CClockFilter::GetMidiOutputNames() const
{
    return {};
}

int CClockFilter::OnProcess(const std::vector<void *> &/*SourceBuffers*/,
                                   const std::vector<void *> &DestinationBuffers,
                                   const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                   const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                   int NumFrames,
                                   std::uint32_t /*TimeStamp*/)
{
    float* ClockBuffer = (float*)(DestinationBuffers[0]);
    if(ClockBuffer)
    {
        *ClockBuffer = m_Clock();
        ++ClockBuffer;
    }

    return 0;
}

void CClockFilter::SetBeatsPerMinute(int Bpm)
{
    m_Clock.SetBeatsPerMinute(Bpm);
}

void CClockFilter::SetBeatsPerBar(int Bpb)
{
    m_Clock.SetBarsPerBeat(Bpb);
}

void CClockFilter::SetSubDivision(int SubDivision)
{
    m_Clock.SetSubDivision(SubDivision);
}
