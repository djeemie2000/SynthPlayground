#include "BasicSamplerFilter.h"

CBasicSamplerFilter::CBasicSamplerFilter(int SamplingFrequency)
    : m_SamplingFrequency(SamplingFrequency)
    , m_Reader()
    , m_PlayerIndex()
    , m_PlayerLeft()
    , m_PlayerRight()
    , m_DefaultOutLeft(4096, 0.0f)
    , m_DefaultOutRight(4096, 0.0f)
    , m_DefaultGateOut(4096, 0.0f)
{
}

std::vector<std::string> CBasicSamplerFilter::GetInputNames() const
{
    return {"Gate"};
}

std::vector<std::string> CBasicSamplerFilter::GetOutputNames() const
{
    return {"OutL", "OutR", "OutGate"};
}

std::vector<std::string> CBasicSamplerFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CBasicSamplerFilter::GetMidiOutputNames() const
{
    return {};
}

int CBasicSamplerFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                             const std::vector<void *> &DestinationBuffers,
                             const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                             const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                             int NumFrames,
                             std::uint32_t /*TimeStamp*/)
{
    if(static_cast<int>(m_DefaultOutLeft.size())<NumFrames)
    {
        m_DefaultOutLeft.resize(NumFrames, 0.0f);
    }
    if(static_cast<int>(m_DefaultOutRight.size())<NumFrames)
    {
        m_DefaultOutRight.resize(NumFrames, 0.0f);
    }
    if(static_cast<int>(m_DefaultGateOut.size())<NumFrames)
    {
        m_DefaultGateOut.resize(NumFrames, 0.0f);
    }

    if(const float* GateInBuffer = static_cast<const float*>(SourceBuffers[0]))
    {
        const float* GateInBufferEnd = GateInBuffer + NumFrames;

        float* OutLeftBuffer = DestinationBuffers[0] ? static_cast<float*>(DestinationBuffers[0]) : m_DefaultOutLeft.data();
        float* OutRightBuffer = DestinationBuffers[1] ? static_cast<float*>(DestinationBuffers[1]) : m_DefaultOutRight.data();
        float* OutGateBuffer = DestinationBuffers[2] ? static_cast<float*>(DestinationBuffers[2]) : m_DefaultGateOut.data();

        const float PlaybackSpeed = m_Reader.GetSamplingFrequency()/m_SamplingFrequency;

        const float* LD = m_Reader.GetLeft().data();
        const float* RD = m_Reader.GetRight().data();
        int Size = m_Reader.GetSize();
        CTriggerIn<float> TriggerIn;
        while(GateInBuffer<GateInBufferEnd)
        {
            if(TriggerIn.IsTriggerOn(m_GateToTrigger(*GateInBuffer)))
            {
                m_PlayerIndex.Sync();
            }

            float Index = m_PlayerIndex(PlaybackSpeed);
            bool IsPlaying = false;
            m_PlayerLeft(LD, Size, Index, *OutLeftBuffer, IsPlaying);
            m_PlayerRight(RD, Size, Index, *OutRightBuffer, IsPlaying);
            *OutGateBuffer = IsPlaying ? 1 : 0;

            ++GateInBuffer;
            ++OutLeftBuffer;
            ++OutRightBuffer;
            ++OutGateBuffer;
        }
    }
    return 0;
}

void CBasicSamplerFilter::OnLoad(const std::string &Path)
{
    m_Reader.Read(Path);
}
