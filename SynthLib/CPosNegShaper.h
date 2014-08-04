#ifndef CPOSNEGSHAPER_H
#define CPOSNEGSHAPER_H

template<class T>
class CPosNegShaper
{
public:
    CPosNegShaper()
     : m_PosInvert(false)
     , m_NegInvert(false)
     , m_PosDerectify(false)
     , m_NegDerectify(false)
    {}

    void SetPosInvert(bool Invert)
    {
        m_PosInvert = Invert;
    }

    void SetNegInvert(bool Invert)
    {
        m_NegInvert = Invert;
    }

    void SetPosDerectify(bool Derectify)
    {
        m_PosDerectify = Derectify;
    }

    void SetNegDerectify(bool Derectify)
    {
        m_NegDerectify = Derectify;
    }

    T operator()(T In)
    {
        // derectify means [0,1] to [-1,+1] conversion
        if(0<In)
        { // pos
            T Out = m_PosInvert ? 1-In : In;
            return m_PosDerectify ? 2*Out-1 : Out;
        }

        T Out = m_NegInvert ? -In-1 : In;
        return m_NegDerectify ? 1+2*Out : Out;
    }

private:
    bool m_PosInvert;
    bool m_NegInvert;
    bool m_PosDerectify;
    bool m_NegDerectify;
};

#endif // CPOSNEGSHAPER_H
