#ifndef RINGSEQUENCER_H
#define RINGSEQUENCER_H

template<class T>
class CRingSequencer
{
public:
    static constexpr T MinValue = static_cast<T>(0);
    static constexpr T MaxValue = static_cast<T>(1);
    static constexpr T ValueRange = MaxValue - MinValue;

    CRingSequencer()
        : m_Value(MinValue)
    {}

    void Sync(T Value)
    {
        if(MinValue<= Value && Value<=MaxValue)
        {
            m_Value = Value;
        }
    }

    T operator()(bool Trigger, T Step)
    {
        if(Trigger)
        {
            if(MinValue<= Step && Step<=MaxValue)
            {
                m_Value += Step;
                if(MaxValue<m_Value)
                {
                    m_Value -= ValueRange;
                }
                else if(m_Value<MinValue)
                {
                    m_Value += ValueRange;
                }
            }
        }
        return m_Value;
    }

private:
    T m_Value;
};

#endif // RINGSEQUENCER_H
