#include <algorithm>
#include "OscillatorFilter.h"
#include "SelectableOperatorFactory.h"

COperatorFilter::COperatorFilter()
 : m_Operator(CSelectableOperatorFactory::Create())
{
    m_Operator.Select(0);
}

std::vector<std::string> COperatorFilter::GetInputNames() const
{
    return { "Phase" };
}

std::vector<std::string> COperatorFilter::GetOutputNames() const
{
    return { "Out" };
}

int COperatorFilter::OnProcess(const std::vector<void *> &SourceBuffers, const std::vector<void *> &DestinationBuffers, int NumFrames, std::uint32_t /*TimeStamp*/)
{
    const float* PhaseBuffer = static_cast<const float*>(SourceBuffers[0]);
    float* OutBuffer = static_cast<float*>(DestinationBuffers[0]);
    if(PhaseBuffer && OutBuffer)
    {
        std::transform(PhaseBuffer, PhaseBuffer+NumFrames, OutBuffer, m_Operator);
    }

    return 0;
}

void COperatorFilter::Select(int Selection)
{
    m_Operator.Select(Selection);
}
