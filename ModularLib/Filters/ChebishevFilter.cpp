#include "ChebishevFilter.h"
#include "Chebishev.h"

CChebishevFilter::CChebishevFilter()
    : m_Buffers(std::vector<float>(1+Size, 0.0f), {0.0f})
{
}

std::vector<std::string> CChebishevFilter::GetInputNames() const
{
    std::vector<std::string> Names = {"In"};
    for(std::size_t idx = 1; idx<=Size; ++idx)
    {
        Names.push_back("Ampl"+std::to_string(idx));
    }
    return Names;
}

std::vector<std::string> CChebishevFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CChebishevFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CChebishevFilter::GetMidiOutputNames() const
{
    return {};
}

int CChebishevFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                            const std::vector<void *> &DestinationBuffers,
                            const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                            const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                            int NumFrames,
                            std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const float* In = m_Buffers.GetSourceBuffer(0);
    const float* Ampl1 = m_Buffers.GetSourceBuffer(1);
    const float* Ampl2 = m_Buffers.GetSourceBuffer(2);
    const float* Ampl3 = m_Buffers.GetSourceBuffer(3);
    const float* Ampl4 = m_Buffers.GetSourceBuffer(4);
    const float* Ampl5 = m_Buffers.GetSourceBuffer(5);
    const float* Ampl6 = m_Buffers.GetSourceBuffer(6);
    float * Out = m_Buffers.GetDestinationBuffer(0);
    const float* OutEnd = Out + NumFrames;
    while(Out<OutEnd)
    {
        *Out = (*Ampl1) * Chebishev1(*In)
                + (*Ampl2) * Chebishev2(*In)
                + (*Ampl3) * Chebishev3(*In)
                + (*Ampl4) * Chebishev4(*In)
                + (*Ampl5) * Chebishev5(*In)
                + (*Ampl6) * Chebishev6(*In);

        ++Out;
        ++In;
        ++Ampl1;
        ++Ampl2;
        ++Ampl3;
        ++Ampl4;
        ++Ampl5;
        ++Ampl6;
    }

    return 0;
}
