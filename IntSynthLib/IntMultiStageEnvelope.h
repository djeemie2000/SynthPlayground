#pragma once

namespace isl
{

template<class T, int NumStages, int Scale>
class CMultiStageEnvelope
{
public:
    CMultiStageEnvelope()
     : m_Stage(NumStages-1)
     , m_Counter(0)
     , m_Stages()
     , m_Hold(false)
    {}

    void SetTarget(int Stage, T Target)
    {
        m_Stages[Stage].s_Target = Target;
    }

    void SetDuration(int Stage, T Duration)
    {
        m_Stages[Stage].s_Duration = Duration;
    }

    void SetHold(int Stage, bool Hold)
    {
        m_Stages[Stage].s_Hold = Hold;
    }

    void NoteOn()
    {
        m_Gate = true;
        Reset();
    }

    void NoteOff()
    {
        m_Gate = false;
    }

    void Reset()
    {
        m_Stage = 0;
        m_Counter = 0;
    }

    T operator()()
    {
        T Counter = m_Counter;

        if(m_Stages[m_Stage].s_Duration<=m_Counter)
        {
            // advance or halt
            // last stage : halt -> keep current counter until next reset()
            // other stage: advance to next stage (counter zero)
            if(m_Stage<LastStage)
            {
                ++m_Stage;
                Counter = 0;
                m_Counter = 1;
            }
            // else: last stage => keep counter
        }
        else
        {
            ++m_Counter;
        }

        // handle hold
        m_Hold = m_Stages[m_Stage].s_Hold && m_Gate;
        if(m_Hold)
        {
            m_Counter = 0;
        }

        // linear interpolation between stages
        T Duration = m_Stages[m_Stage].s_Duration;
        T Reference = m_Stages[m_Stage].s_Target;
        // target: for last stage, keep target
        T Target = m_Stage==LastStage ? Reference : m_Stages[m_Stage+1].s_Target;

        T Value = Duration ? Reference + (Target-Reference)*Counter/Duration : Reference;

        return Value;
    }

    int GetStage() const
    {
        return m_Stage;
    }

    bool GetHold() const
    {
        return m_Hold;
    }

private:
    const int LastStage = NumStages-1;

    struct SStage
    {
        T s_Target;
        T s_Duration;
        bool s_Hold;

        SStage()
         : s_Target(0)
         , s_Duration(0)
         , s_Hold(false)
        {}
    };

    int m_Stage;
    T m_Counter;
    bool m_Gate;
    SStage  m_Stages[NumStages];
    bool m_Hold;
};

}
