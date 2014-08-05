#ifndef CPOSNEGSHAPER_H
#define CPOSNEGSHAPER_H


template<class T>
class CPosNegInverter
{
public:
    CPosNegInverter()
     : m_PosInvert(false)
     , m_NegInvert(false)
    {}

    void SetPosInvert(bool Invert)
    {
        m_PosInvert = Invert;
    }

    void SetNegInvert(bool Invert)
    {
        m_NegInvert = Invert;
    }

    T operator()(T In)
    {
        if(0<In)
        { // pos
            return m_PosInvert ? 1-In : In;
        }
        return m_NegInvert ? -In-1 : In;
    }

private:
    bool m_PosInvert;
    bool m_NegInvert;
};

template<class T>
class CPosNegDerectifier
{
public:
    CPosNegDerectifier()
     : m_PosDerectify(false)
     , m_NegDerectify(false)
    {}

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
            return m_PosDerectify ? 2*In-1 : In;
        }

        return m_NegDerectify ? 1+2*In : In;
    }

private:
    bool m_PosDerectify;
    bool m_NegDerectify;
};

#endif // CPOSNEGSHAPER_H
