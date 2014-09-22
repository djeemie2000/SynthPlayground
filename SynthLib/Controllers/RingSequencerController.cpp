#include "RingSequencerController.h"


CRingSequencerController::CRingSequencerController(int SamplingFrequency,
                                                   std::shared_ptr<IMidiHandler> MidiInputHandler,
                                                   std::shared_ptr<IMidiSource> MidiSource)
 : m_MidiInputHandler(MidiInputHandler)
 , m_MidiSource(MidiSource)
 , m_Counter(0)
 , m_PeriodSamples(SamplingFrequency)
 , m_Active(false)
 , m_MidiControllerStep()
{
    m_PeriodSamples.SetBeatsPerMinute(120);
    m_PeriodSamples.SetBarsPerBeat(4);
}

int CRingSequencerController::OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp)
{
    if(m_Active)
    {
        int Frame = 0;
        while(Frame<NumFrames)
        {
            if(m_Counter==0)
            {
                for(auto& Step : m_MidiControllerStep)
                {
                    Step.Apply(*m_MidiInputHandler, Frame);
                }
            }

            ++m_Counter;
            if(m_PeriodSamples.PeriodSamples()<=m_Counter)
            {
                m_Counter = 0;
            }

            ++Frame;
        }

        return m_MidiSource->OnRead(Dst, NumFrames, TimeStamp);
    }

    return 0;
}

void CRingSequencerController::SetBeatsPerMinute(int Bpm)
{
    m_PeriodSamples.SetBeatsPerMinute(Bpm);
}

void CRingSequencerController::SetBarsPerBeat(int BarsPerBeat)
{
    m_PeriodSamples.SetBarsPerBeat(BarsPerBeat);
}

void CRingSequencerController::Activate(bool Active)
{
    m_Active = Active;
}

bool CRingSequencerController::CheckResize(int Idx)
{
    if(0<=Idx)
    {
        if(static_cast<int>(m_MidiControllerStep.size())<=Idx)
        {
            m_MidiControllerStep.resize(Idx+1);
        }
        return true;
    }
    return false;
}

void CRingSequencerController::SetMidiController(int Idx, int MidiController)
{
    if(CheckResize(Idx))
    {
        m_MidiControllerStep[Idx].SetMidiController(MidiController);
    }
}

void CRingSequencerController::SetStep(int Idx, int Step)
{
    if(CheckResize(Idx))
    {
        m_MidiControllerStep[Idx].SetStep(Step);
    }
}

void CRingSequencerController::SetStart(int Idx, int Start)
{
    if(CheckResize(Idx))
    {
        m_MidiControllerStep[Idx].SetStart(Start);
    }
}

void CRingSequencerController::SetMin(int Idx, int Min)
{
    if(CheckResize(Idx))
    {
        m_MidiControllerStep[Idx].SetMin(Min);
    }
}

void CRingSequencerController::SetMax(int Idx, int Max)
{
    if(CheckResize(Idx))
    {
        m_MidiControllerStep[Idx].SetMax(Max);
    }
}

void CRingSequencerController::SetActive(int Idx, bool Active)
{
    if(CheckResize(Idx))
    {
        m_MidiControllerStep[Idx].SetActive(Active);
    }
}
