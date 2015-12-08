#pragma once

namespace isl
{

template<class T, int NumStages, int Scale>
class CMultiStageEnvelope
{
public:
    CMultiStageEnvelope()
     : m_Stage(0)
     , m_Counter(0)
     , m_State(PreGate)
     , m_Stages()
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
        m_State = TriggerOn;
        Reset();
    }

    void NoteOff()
    {
        m_State = TriggerOff;
    }

    void Reset()
    {
        m_Stage = 0;
        m_Counter = 0;
    }

    T operator()()
    {
        if(m_State == PreGate)
        {
            // stay at current (reset state)
        }
        else if(m_State == TriggerOn)
        {
            // stay at current (reset state)
            // but make sure we start advancing the next time
            m_State = Gate;
        }
        else if(m_State == Gate)
        {
            // advance, unless we are in a hold stage
            if(!m_Stages[m_Stage].s_Hold)
            {
                Advance();
            }
        }
        else if(m_State == TriggerOff)
        {
            // if in hold state => advance trough remaining stages
            // if no in hold state => reset
            if(m_Stages[m_Stage].s_Hold)
            {
                m_State = PostGate;// needed?
            }
            else
            {
                m_State = PreGate;
                Reset();
            }
        }
        else if(m_State == PostGate)
        {
            // always advance??
            Advance();
        }

        T Value = CalcValue();

        return Value;
    }

    int GetStage() const
    {
        return m_Stage;
    }

    bool GetHold() const
    {
        return m_Stages[m_Stage].s_Hold && m_State == Gate;
    }

private:
    T CalcValue()
    {
        T Counter = m_Counter;
        // linear interpolation between stages
        T Duration = m_Stages[m_Stage].s_Duration;
        T Reference = m_Stages[m_Stage].s_Target;
        // target: for last stage, keep target
        T Target = m_Stage==LastStage ? Reference : m_Stages[m_Stage+1].s_Target;

        T Value = Duration ? Reference + (Target-Reference)*Counter/Duration : Reference;

        return Value;
    }

    void Advance()
    {
        ++m_Counter;
        if(m_Stages[m_Stage].s_Duration<=m_Counter)
        {
            if(m_Stage<LastStage)
            {
                ++m_Stage;
                m_Counter = 0;
            }
        }
    }

    const int LastStage = NumStages-1;

    enum EGate
    {
        PreGate,
        TriggerOn,
        Gate,
        TriggerOff,
        PostGate
    };

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
    EGate m_State;
    SStage  m_Stages[NumStages];
};

}
