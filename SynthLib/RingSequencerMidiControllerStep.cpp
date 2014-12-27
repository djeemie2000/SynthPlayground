#include "RingSequencerMidiControllerStep.h"
#include "MidiHandlerI.h"

namespace
{

const int LowestMin = 0;
const int HighestMax = 128;

}

CRingSequencerMidiControllerStep::CRingSequencerMidiControllerStep()
 : m_MidiController(-1)
 , m_Active(false)
 , m_Min(LowestMin)
 , m_Max(HighestMax)
 , m_Start(64)
 , m_Step(1)
 , m_Value(64)
{
}

void CRingSequencerMidiControllerStep::SetMidiController(int MidiController)
{
    if(-1<=MidiController && MidiController<HighestMax)
    {
        m_MidiController = MidiController;
    }
}

void CRingSequencerMidiControllerStep::SetStep(int Step)
{
    // note: step can be negative
    // does not make sense to be outside the interval ]-HighestMax, HighestMax[ even though this does not do anything wrong
    m_Step = Step%HighestMax;
}

void CRingSequencerMidiControllerStep::SetStart(int Start)
{
    if(LowestMin<=Start && Start<HighestMax)
    {
        m_Start = Start;
    }
}

void CRingSequencerMidiControllerStep::SetMin(int Min)
{
    if(LowestMin<=Min && Min<HighestMax)
    {
        m_Min = Min;//TODO check min < max?
    }
}

void CRingSequencerMidiControllerStep::SetMax(int Max)
{
    if(LowestMin<=Max && Max<=HighestMax)
    {
        m_Max = Max;
    }
}

void CRingSequencerMidiControllerStep::SetActive(bool Active)
{
    if(Active != m_Active)
    {
        if(Active)
        {
            m_Value = m_Start;
        }
        m_Active = Active;
    }
}

void CRingSequencerMidiControllerStep::Update()
{
    m_Value = m_Min + (m_Value - m_Min + m_Step)%(m_Max-m_Min);
}

void CRingSequencerMidiControllerStep::Apply(IMidiHandler &Handler, std::uint32_t TimeStamp)
{
    Update();

    if(m_MidiController!=-1 && m_Active)
    {
        Handler.OnController(m_MidiController, m_Value, TimeStamp);
    }
}
