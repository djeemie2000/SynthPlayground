#ifndef ASYMMETRICAMP_H
#define ASYMMETRICAMP_H

template<class T>
class CAsymmetricAmp
{
public:
    CAsymmetricAmp()
        : m_AmpPos(1)
        , m_AmpNeg(1)
        , m_Offset(0)
        , m_OffsetLockMode(false)
    {}

    void SetAmpPos(T AmpPos)
    {
        m_AmpPos = AmpPos;
    }

    void SetAmpNeg(T AmpNeg)
    {
        m_AmpNeg = AmpNeg;
    }

    void SetOffset(T Offset)
    {
        m_Offset = Offset;
    }

    void SetOffsetLockMode(bool Mode)
    {
        m_OffsetLockMode = Mode;
    }

    T operator()(T In)
    {
        // TODO this could be more elegantly handled?
        if(m_OffsetLockMode)
        {
            return m_Offset + (0<In ? (1-m_Offset)*In : (1+m_Offset)*In);
        }
        return m_Offset + (0<In ? m_AmpPos*In : m_AmpNeg*In);
    }

private:
    T m_AmpPos;
    T m_AmpNeg;
    T m_Offset;

    bool m_OffsetLockMode;
};

#endif // ASYMMETRICAMP_H
