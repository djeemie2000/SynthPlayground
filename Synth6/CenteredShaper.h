#ifndef CENTEREDSHAPER_H
#define CENTEREDSHAPER_H

template<class T>
class CCenteredShaper
{
public:
    CCenteredShaper()
     : m_Slope(1)
     , m_CenterY(0.5)
    {
    }

    void SetSlope(T Slope)
    {
        m_Slope = Slope;
    }

    void SetCenter(T Center)
    {
        m_CenterY = Center;
    }


    T operator()(const T& Phase) const
    {
        // Out-Center.y = slope * (In - Center.x)
        const T CenterX = 0.5;
        //const T CenterY = 0.5;
        T Value = m_CenterY + m_Slope*(Phase-CenterX);
        Value = Value<0 ? 0 : Value;
        Value = 1<Value ? 1 : Value;
        return Value;
    }
private:
    T m_Slope;
    T m_CenterY;
};


#endif // CENTEREDSHAPER_H
