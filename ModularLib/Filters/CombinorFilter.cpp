#include <algorithm>
#include "CombinorFilter.h"
#include "SelectableCombinor.h"
#include "SelectableCombinorFactory.h"

CCombinorFilter::CCombinorFilter()
 : m_Combinor(CSelectableCombinorFactory::Create())
{
    Select(0);//need to do this!
}

std::vector<std::string> CCombinorFilter::GetInputNames() const
{
    return { "In1", "In2" };
}

std::vector<std::string> CCombinorFilter::GetOutputNames() const
{
    return { "Out" };
}

std::vector<std::string> CCombinorFilter::GetMidiInputNames() const
{
    return {};
}

int CCombinorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                          const std::vector<void *> &DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                          int NumFrames,
                          std::uint32_t /*TimeStamp*/)
{
    const float* In1Buffer = static_cast<const float*>(SourceBuffers[0]);
    const float* In2Buffer = static_cast<const float*>(SourceBuffers[1]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(In1Buffer && OutBuffer && In2Buffer)
    {
        std::transform(In1Buffer, In1Buffer+NumFrames, In2Buffer, OutBuffer, m_Combinor);//TODO
    }

    return 0;
}

void CCombinorFilter::Select(int Selected)
{
    m_Combinor.Select(Selected);
}
