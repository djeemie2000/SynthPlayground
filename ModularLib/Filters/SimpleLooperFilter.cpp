#include "SimpleLooperFilter.h"

CSimpleLooperFilter::CSimpleLooperFilter(int SamplingFrequency)
    : m_LoopRecorder(32*SamplingFrequency)// higher capacity ???
    , m_DefaultRecordGate(4096, 0.0f)
    , m_DefaultIn(4096, 0.0f)
    , m_DefaultOut(4096, 0.0f)
{
}

std::vector<std::string> CSimpleLooperFilter::GetInputNames() const
{
    return {"In", "RecordGate"};
}

std::vector<std::string> CSimpleLooperFilter::GetOutputNames() const
{
    return {"Out"};
}

std::vector<std::string> CSimpleLooperFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CSimpleLooperFilter::GetMidiOutputNames() const
{
    return {};
}

int CSimpleLooperFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                             const std::vector<void *> &DestinationBuffers,
                             const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                             const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                             int NumFrames,
                             std::uint32_t /*TimeStamp*/)
{
    if(static_cast<int>(m_DefaultRecordGate.size())<NumFrames)
    {
        m_DefaultRecordGate.resize(NumFrames, 0.0f);
    }
    if(static_cast<int>(m_DefaultIn.size())<NumFrames)
    {
        m_DefaultIn.resize(NumFrames, 0.0f);
    }
    if(static_cast<int>(m_DefaultOut.size())<NumFrames)
    {
        m_DefaultOut.resize(NumFrames, 0.0f);
    }

    const float* InBuffer = SourceBuffers[0] ? static_cast<const float*>(SourceBuffers[0]) : m_DefaultIn.data();
    const float* RecordGateBuffer = SourceBuffers[1] ? static_cast<const float*>(SourceBuffers[1]) : m_DefaultRecordGate.data();
    const float* InBufferEnd = InBuffer + NumFrames;
    float* OutBuffer = DestinationBuffers[0] ? static_cast<float*>(DestinationBuffers[0]) : m_DefaultOut.data();

    const float PlaybackSpeed = 1.0f;
    while(InBuffer<InBufferEnd)
    {
        bool Recording = m_LoopRecorder(*RecordGateBuffer, *InBuffer);
        // during recording, playback input, after recording, start playing back the loop
        if(Recording)
        {
            m_LoopPlayer.Sync();
            *OutBuffer = *InBuffer;
        }
        else
        {
            *OutBuffer = m_LoopPlayer(m_LoopRecorder.GetData(), m_LoopRecorder.GetSize(), PlaybackSpeed);
        }

        ++RecordGateBuffer;
        ++InBuffer;
        ++OutBuffer;
    }

    return 0;
}
