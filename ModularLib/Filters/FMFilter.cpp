#include <algorithm>
#include "FMFilter.h"

CFMFilter::CFMFilter(int SamplingFrequency)
 : m_FM(SamplingFrequency)
{
}

std::vector<std::string> CFMFilter::GetInputNames() const
{
    return { "CarrierFreq", "ModAmpl", "ModFreqMult" };
}

std::vector<std::string> CFMFilter::GetOutputNames() const
{
    return { "FMFreq" };
}

std::vector<std::string> CFMFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CFMFilter::GetMidiOutputNames() const
{
    return {};
}

int CFMFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* FreqInBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* ModAmplitudeBuffer = static_cast<const float*>(SourceBuffers[1]);
    const float* FreqMultInBuffer = static_cast<const float*>(SourceBuffers[2]);
    float* FreqOutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(FreqInBuffer && ModAmplitudeBuffer && FreqMultInBuffer && FreqOutBuffer)
    {
        const float* FreqInBufferEnd = FreqInBuffer+NumFrames;
        while(FreqInBuffer<FreqInBufferEnd)
        {
            *FreqOutBuffer = m_FM(*FreqInBuffer, *ModAmplitudeBuffer, *FreqMultInBuffer);
            ++FreqInBuffer;
            ++ModAmplitudeBuffer;
            ++FreqMultInBuffer;
            ++FreqOutBuffer;
        }
    }
    else if(FreqInBuffer && FreqOutBuffer)
    {
        // no mod amplitude => freq out = freq in
        // no mult frequency => ??
        std::copy(FreqInBuffer, FreqInBuffer+NumFrames, FreqOutBuffer);
    }
    else if(FreqOutBuffer)
    {
        std::fill(FreqOutBuffer, FreqOutBuffer+NumFrames, 440.0f);
    }

    return 0;
}

void CFMFilter::SelectModulatorWaveform(int Selection)
{
    m_FM.SelectModulatorWaveform(Selection);
}
