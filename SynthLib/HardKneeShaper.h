#ifndef HARDKNEESHAPER_H
#define HARDKNEESHAPER_H

template<class T>
class CHardKneeShaper
{
public:
    CHardKneeShaper()
     : m_X(0.5)
     , m_Y(0.5)
    {
    }

    void SetKnee(T X, T Y)
    {
        // X and Y should be in ]0,1[
        if(0<=X && X<=1 && 0<=Y && Y<=1)
        {
            m_X = X;
            m_Y = Y;
        }
    }

    T operator()(const T& Phase) const
    {
        // calculated these formulas
        // TODO rework!
        return Phase < m_X ? m_Y * Phase / m_X : 1 - (1-m_Y)*(1-Phase)/(1-m_X);
    }
private:
    T m_X;
    T m_Y;
};

#endif // HARDKNEESHAPER_H
