#include <algorithm>
#include "PhaseShifterFilter.h"
#include "PhaseShifter.h"

CPhaseShifterFilter::CPhaseShifterFilter()
 : m_Shifter()
{
}

std::vector<std::string> CPhaseShifterFilter::GetInputNames() const
{
    return { "Phase", "Shift" };
}

std::vector<std::string> CPhaseShifterFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CPhaseShifterFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CPhaseShifterFilter::GetMidiOutputNames() const
{
    return {};
}

int CPhaseShifterFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* PhaseBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* ShiftBuffer = static_cast<const float*>(SourceBuffers[1]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(PhaseBuffer && OutBuffer && ShiftBuffer)
    {
        std::transform(PhaseBuffer, PhaseBuffer+NumFrames, ShiftBuffer, OutBuffer, m_Shifter);
    }
    else if(PhaseBuffer && OutBuffer)
    {
        // no shift = zero shift
        std::copy(PhaseBuffer, PhaseBuffer+NumFrames, OutBuffer);
    }
    else if(OutBuffer)
    {
        std::fill(OutBuffer, OutBuffer+NumFrames, 0);
    }

    return 0;
}
