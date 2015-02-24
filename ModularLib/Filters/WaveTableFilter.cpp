#include <algorithm>
#include "WaveTableFilter.h"
#include "WaveTables/WaveTableData.h"

CWaveTableFilter::CWaveTableFilter()
 : m_Manager(wt2::wav_res_waves, sizeof(wt2::wav_res_waves), 129)//128 or 129??
{
}

std::vector<std::string> CWaveTableFilter::GetInputNames() const
{
    return { "Phase", "Begin", "Length" };
}

std::vector<std::string> CWaveTableFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CWaveTableFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CWaveTableFilter::GetMidiOutputNames() const
{
    return {};
}

int CWaveTableFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(OutBuffer)
    {
        const float* PhaseBuffer = static_cast<const float*>(SourceBuffers[0]);
        const float* BeginBuffer = static_cast<const float*>(SourceBuffers[1]);
        const float* LengthBuffer = static_cast<const float*>(SourceBuffers[2]);

        if(PhaseBuffer && BeginBuffer && LengthBuffer)
        {
            float* OutEnd = OutBuffer + NumFrames;
            while(OutBuffer<OutEnd)
            {
                *OutBuffer = m_Manager(*PhaseBuffer, *BeginBuffer, *LengthBuffer);
                ++OutBuffer;
                ++PhaseBuffer;
                ++BeginBuffer;
                ++LengthBuffer;
            }
        }
        else if(PhaseBuffer && BeginBuffer)
        {
            float* OutEnd = OutBuffer + NumFrames;
            while(OutBuffer<OutEnd)
            {
                *OutBuffer = m_Manager(*PhaseBuffer, *BeginBuffer, 0);
                ++OutBuffer;
                ++PhaseBuffer;
                ++BeginBuffer;
            }
        }
        else if(PhaseBuffer && LengthBuffer)
        {
            float* OutEnd = OutBuffer + NumFrames;
            while(OutBuffer<OutEnd)
            {
                *OutBuffer = m_Manager(*PhaseBuffer, 0, *LengthBuffer);
                ++OutBuffer;
                ++PhaseBuffer;
                ++LengthBuffer;
            }
        }
        else
        {
            std::fill(OutBuffer, OutBuffer + NumFrames, 0);
        }
    }

    return 0;
}
