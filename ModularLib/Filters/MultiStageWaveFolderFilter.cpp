#include <algorithm>
#include "MultiStageWaveFolderFilter.h"

CMultiStageWaveFolderFilter::CMultiStageWaveFolderFilter()
 : m_MultiStageWaveFolder()
{
}

std::vector<std::string> CMultiStageWaveFolderFilter::GetInputNames() const
{
    return {"In", "Fold"};
}

std::vector<std::string> CMultiStageWaveFolderFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CMultiStageWaveFolderFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CMultiStageWaveFolderFilter::GetMidiOutputNames() const
{
    return {};
}

int CMultiStageWaveFolderFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    if(const float* InBuffer = static_cast<const float*>(SourceBuffers[0]))
    {
        if(const float* FoldBuffer = static_cast<const float*>(SourceBuffers[1]))
        {
            if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
            {
                const float* DstBufferEnd = DstBuffer + NumFrames;
                while(DstBuffer<DstBufferEnd)
                {                   
                    *DstBuffer = m_MultiStageWaveFolder(*InBuffer, *FoldBuffer);
                    ++InBuffer;
                    ++FoldBuffer;
                    ++DstBuffer;
                }
            }
        }
    }
    else
    {
        if(float* DstBuffer = static_cast<float*>(DestinationBuffers[0]))
        {
            std::fill(DstBuffer, DstBuffer + NumFrames, 0.0f);
        };
    }

    return 0;
}

void CMultiStageWaveFolderFilter::SetNumStages(int NumStages)
{
    m_MultiStageWaveFolder.SetNumStages(NumStages);
}
