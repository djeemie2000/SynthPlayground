#ifndef INVERTER_H
#define INVERTER_H

template<class T>
class CInverter
{
public:
    CInverter()
     : m_InvertPos(false)
     , m_InvertNeg(false)
    {}

    void SetInvertNeg(bool Invert)
    {
        m_InvertNeg = Invert;
    }

    void SetInvertPos(bool Invert)
    {
        m_InvertPos = Invert;
    }

    T operator()(T In)
    {
        return In<0 ? (m_InvertNeg ? In-1 : In) : (m_InvertPos ? 1-In : In);
    }

private:
    bool m_InvertPos;
    bool m_InvertNeg;
};

#endif // INVERTER_H
