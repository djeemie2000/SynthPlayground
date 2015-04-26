#pragma once

template<class T>
class CControllerChange
{
public:
    static constexpr T MinValue = static_cast<T>(0);
    static constexpr T MaxValue = static_cast<T>(1);
    static constexpr T ValueRange = MaxValue - MinValue;

    CControllerChange()
        : m_Value(MinValue)
    {}

    void Sync(T Value)
    {
        if(MinValue<= Value && Value<=MaxValue)
        {
            m_Value = Value;
        }
    }

    T operator()(T Increase, T Decrease, T Rate)
    {
        // Incr and Decr are usually gates (0 or 1)
        // which trigger an increase/decrease of the value
        m_Value += Rate*(Increase-Decrease);

        // limit value to [0,1]
        if(m_Value<MinValue)
        {
            m_Value = MinValue;
        }
        else if(MaxValue< m_Value)
        {
            m_Value = MaxValue;
        }

        return m_Value;
    }

private:
    T m_Value;
};
