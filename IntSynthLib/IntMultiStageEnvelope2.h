#pragma once

namespace isl
{

template<class T, int NumStages, int Scale>
class CMultiStageEnvelope2
{
public:
    enum EAction
    {
        AdvanceAction,
        HoldAction,
        ResetAction,
        SkipAction
    };

    CMultiStageEnvelope2()
     : m_Stage(0)
     , m_Counter(0)
     , m_State(GateOff)
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

    void SetAction(int Stage, bool Gate, EAction Action)
    {
        if(Gate)
        {
            m_Stages[Stage].s_GateOnAction = Action;
        }
        else
        {
            m_Stages[Stage].s_GateOffAction = Action;
        }
    }

    void NoteOn()
    {
        m_State = GateOn;//TriggerOn;
        //Reset();
    }

    void NoteOff()
    {
        m_State = GateOff;//TriggerOff;
    }

    void Reset()
    {
        m_Stage = 0;
        m_Counter = 0;
    }

    T operator()()
    {
        T Value = CalcValue();

        bool Gate = (m_State == GateOn);
//        if(m_State == TriggerOn)
//        {
//            // stay at current (reset state)
//            // but make sure we start advancing the next time
//            m_State = GateOn;
//            Gate = false;
//        }
//        else if(m_State == GateOn)
//        {
//            Gate = true;
//        }
//        else if(m_State == TriggerOff)
//        {
//            m_State = GateOff;
//            Gate = true;
//        }
//        else if(m_State == TriggerOff)
//        {
//            Gate = false;
//        }

        EAction CurrentAction = Gate ? m_Stages[m_Stage].s_GateOnAction : m_Stages[m_Stage].s_GateOffAction;

        if(CurrentAction==AdvanceAction)
        {
            Advance();
        }
        else if(CurrentAction==HoldAction)
        {
            // hold -> do nothing
        }
        else if(CurrentAction==ResetAction)
        {
            Reset();
        }
        else if(CurrentAction==SkipAction)
        {
            //TODO advance to next stage untill a stage is not skipped
            // potential issue: infinitely skipping?
        }

        return Value;
    }

    int GetStage() const
    {
        return m_Stage;
    }

    bool GetHold() const
    {
        return (m_State == GateOn && m_Stages[m_Stage].s_GateOnAction == HoldAction)
            || (m_State == GateOff && m_Stages[m_Stage].s_GateOffAction == HoldAction);
    }

private:
    T CalcValue()
    {
        T Counter = m_Counter;
        // linear interpolation between stages
        T Duration = m_Stages[m_Stage].s_Duration;
        T Reference = m_Stages[m_Stage].s_Target;
        // target:
        int NextStage = m_Stage<LastStage ? m_Stage+1 : 0;
        T Target = m_Stages[NextStage].s_Target;

        T Value = Duration ? Reference + (Target-Reference)*Counter/Duration : Reference;

        return Value;
    }

    void Advance()
    {
        ++m_Counter;
        if(m_Stages[m_Stage].s_Duration<=m_Counter)
        {
            // advance stage
            ++m_Stage;
            if(NumStages<=m_Stage)
            {
                m_Stage = 0;
            }
            m_Counter = 0;
        }
    }

    const int LastStage = NumStages-1;

    enum EGate
    {
        GateOff,
        //TriggerOn,
        GateOn,
        //TriggerOff
    };

    struct SStage
    {
        T s_Target;
        T s_Duration;
        EAction s_GateOnAction;
        EAction s_GateOffAction;

        SStage()
         : s_Target(0)
         , s_Duration(0)
         , s_GateOnAction(AdvanceAction)
         , s_GateOffAction(HoldAction)
        {}
    };

    int m_Stage;
    T m_Counter;
    EGate m_State;
    SStage  m_Stages[NumStages];
};

}
