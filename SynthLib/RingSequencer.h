#ifndef RINGSEQUENCER_H
#define RINGSEQUENCER_H

template<class T>
class CRingSequencer
{
public:
    static constexpr T MinValue = static_cast<T>(0);
    static constexpr T MaxValue = Static_cast<T>(1);
    static constexpr T ValueRange = MaxValue - MinValue;

    CRingSequencer()
        : m_InternalValue(MinValue)
        , m_Value(MinValue)
    {}

    void Sync(T Value)
    {
        if(MinValue<= Value && Value<=MaxValue)
        {
            m_InternalValue = Value;
        }
    }

    T operator()(bool Trigger, T Step, T Begin, T End)
    {
        if(Trigger)
        {
            if(MinValue<= Step && Step<=MaxValue)
            {
                m_InternalValue += Step;
                if(MaxValue<m_InternalValue)
                {
                    m_InternalValue -= ValueRange;
                }
            }

            m_Value = Begin + (End-Begin)*m_InternalValue;
        }
        return m_Value;
    }

private:
    T m_InternalValue;
    T m_Value;
};

#endif // RINGSEQUENCER_H
