#include <algorithm>
#include "WaveFolderFilter.h"
#include "WaveFolder.h"
#include "SymmetricalOperator.h"

CWaveFolderFilter::CWaveFolderFilter()
{
}

std::vector<std::string> CWaveFolderFilter::GetInputNames() const
{
    return { "In", "Fold" };
}

std::vector<std::string> CWaveFolderFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CWaveFolderFilter::GetMidiInputNames() const
{
    return {};
}

int CWaveFolderFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStWaveFolder*/)
{
    const float* InBuffer = static_cast<const float*>(SourceBuffers[0]);
    const float* FoldBuffer = static_cast<const float*>(SourceBuffers[1]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(InBuffer && OutBuffer && FoldBuffer)
    {
        CSymmetricalOperator<float> SymmWaveFold;
        CWaveFold2<float> WaveFolder;

        const float* OutBufferEnd = OutBuffer + NumFrames;
        while(OutBuffer<OutBufferEnd)
        {
            *OutBuffer = SymmWaveFold(*InBuffer, WaveFolder, *FoldBuffer);
            ++InBuffer;
            ++FoldBuffer;
            ++OutBuffer;
        }
    }

    return 0;
}
