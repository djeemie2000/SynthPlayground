#include <algorithm>
#include "OneVoltPerOctaveFilter.h"
#include "OneVoltPerOctave.h"

COneVoltPerOctaveFilter::COneVoltPerOctaveFilter()
 : m_OneVoltPerOctave(55.0f)//TODO ref frequency!!!!
{
}

std::vector<std::string> COneVoltPerOctaveFilter::GetInputNames() const
{
    return { "CV" };
}

std::vector<std::string> COneVoltPerOctaveFilter::GetOutputNames() const
{
    return { "Freq" };
}

std::vector<std::string> COneVoltPerOctaveFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> COneVoltPerOctaveFilter::GetMidiOutputNames() const
{
    return {};
}

int COneVoltPerOctaveFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStOneVoltPerOctave*/)
{
    if(float* FreqBuffer = static_cast<float*>(DestinationBuffers[0]))
    {
        if(const float* CVBuffer = static_cast<const float*>(SourceBuffers[0]))
        {
            const float* CVBufferEnd = CVBuffer + NumFrames;
            while(CVBuffer<CVBufferEnd)
            {
                *FreqBuffer = m_OneVoltPerOctave(*CVBuffer);
                ++CVBuffer;
                ++FreqBuffer;
            }
        }
        else
        {
            // no input => assume zero CV
            float Freq0 = m_OneVoltPerOctave(0.0f);
            std::fill(FreqBuffer, FreqBuffer+NumFrames, Freq0);
        }
    }

    return 0;
}
