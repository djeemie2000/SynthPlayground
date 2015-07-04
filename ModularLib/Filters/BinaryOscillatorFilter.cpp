#include <algorithm>
#include "BinaryOscillatorFilter.h"
#include "BinaryOscillator.h"

CBinaryOscillatorFilter::CBinaryOscillatorFilter()
 : m_BinaryOscillator()
{
}

std::vector<std::string> CBinaryOscillatorFilter::GetInputNames() const
{
    return { "Phase", "Value" };
}

std::vector<std::string> CBinaryOscillatorFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CBinaryOscillatorFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CBinaryOscillatorFilter::GetMidiOutputNames() const
{
    return {};
}

int CBinaryOscillatorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    // TODO default buffers!
    const float* PhaseBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* BinaryValueBuffer = static_cast<const float*>(SourceBuffers[1]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(PhaseBuffer && OutBuffer && BinaryValueBuffer)
    {
        // binary oscillator is stateless so we can use std::transform
        std::transform(PhaseBuffer, PhaseBuffer+NumFrames, BinaryValueBuffer, OutBuffer, m_BinaryOscillator);
    }

    return 0;
}
