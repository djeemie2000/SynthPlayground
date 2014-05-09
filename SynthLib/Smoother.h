#ifndef SMOOTHER_H
#define SMOOTHER_H

template<class T>
class CSmoother
{
public:
    CSmoother()
        : m_Factor(0)
        , m_Smoothed(0)
    {
    }

    void SetFactor(const T& Factor)
    {
        // should be in[0,1]
        m_Factor = Factor;
    }

    T operator()(const T& Value)
    {
        m_Smoothed = m_Factor*m_Smoothed + (1-m_Factor)*Value;
        return m_Smoothed;
    }

private:
    T m_Factor;
    T m_Smoothed;
};

#endif // SMOOTHER_H
