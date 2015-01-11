#ifndef SLEWLIMITER
#define SLEWLIMITER

template<class T>
class CSlewLimiter
{
public:
    CSlewLimiter(T Initial)
     : m_Value(Initial)
    {}

    void Sync(T Value)
    {
        m_Value = Value;
    }

    T operator()(T In, T SlewPos, T SlewNeg)
    {
        if(In+SlewNeg<m_Value)
        {
            m_Value -= SlewNeg;
        }
        else if(m_Value+SlewPos<In)
        {
            m_Value += SlewPos;
        }
        else
        {
            m_Value = In;
        }
        return m_Value;
    }

private:
    T m_Value;
};

#endif // SLEWLIMITER

