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
     , m_Gate(PostGate)
     , m_Stages()
     //, m_Hold(false)
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
        m_Gate = Gate;
        Reset();
    }

    void NoteOff()
    {
        m_Gate = PostGate;
    }

    void Reset()
    {
        m_Stage = 0;
        m_Counter = 0;
    }

    T operator()()
    {
        bool Advance = (m_Gate==Gate && !m_Stages[m_Stage].s_Hold)
                        || (m_Gate==PostGate);

        if(Advance)
        {
            // advance or halt
            // last stage : halt -> keep current counter until next reset()
            // other stage: advance to next stage (counter zero)
            if(m_Stages[m_Stage].s_Duration<=m_Counter)
            {
                if(m_Stage<LastStage)
                {
                    ++m_Stage;
                    m_Counter = 0;//m_Stages[m_Stage].s_Hold ? 0: 1;
                    Advance = !m_Stages[m_Stage].s_Hold;
                }
            }
//            else
//            {
//                ++m_Counter;
//            }
        }

        T Value = CalcValue();

        if(Advance)
        {
            ++m_Counter;
        }

        // handle hold
        //m_Hold = m_Stages[m_Stage].s_Hold && m_Gate == Gate;
//        if(m_Hold)
//        {
//            m_Counter = 0;
//        }

        return Value;
    }

    int GetStage() const
    {
        return m_Stage;
    }

    bool GetHold() const
    {
        return m_Stages[m_Stage].s_Hold && m_Gate == Gate;//m_Hold;
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

    const int LastStage = NumStages-1;

    enum EGate
    {
        PreGate,
        Gate,
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
    EGate m_Gate;
    SStage  m_Stages[NumStages];
    //bool m_Hold;
};

}
