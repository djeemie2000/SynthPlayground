#include "IntWaveFolderFilter.h"

CIntWaveFolderFilter::CIntWaveFolderFilter()
 : m_WaveFolder()
 , m_Buffers({0.0f, 0.0f}, {0.0f})
{
}

std::vector<std::string> CIntWaveFolderFilter::GetInputNames() const
{
    return { "In", "Fold" };
}

std::vector<std::string> CIntWaveFolderFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CIntWaveFolderFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CIntWaveFolderFilter::GetMidiOutputNames() const
{
    return {};
}

int CIntWaveFolderFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const int ValueMultiplier = 1<<ValueScale;
    const int FoldMultiplier = 1<<FoldScale;

    const float* InBuffer = m_Buffers.GetSourceBuffer(0);
    const float* FoldBuffer = m_Buffers.GetSourceBuffer(1);
    float* OutBuffer = m_Buffers.GetDestinationBuffer(0);
    const float* OutBufferEnd = OutBuffer + NumFrames;
    while(OutBuffer<OutBufferEnd)
    {
        m_WaveFolder.SetFold((*FoldBuffer)*FoldMultiplier);
        float Out = m_WaveFolder((*InBuffer)*ValueMultiplier);
        *OutBuffer = Out/ValueMultiplier;//implicitely upcasted to floats

        ++InBuffer;
        ++FoldBuffer;
        ++OutBuffer;
    }

    return 0;
}
