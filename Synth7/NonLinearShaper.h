#ifndef NONLINEARSHAPER_H
#define NONLINEARSHAPER_H

#include "Conversions.h"

/*!
 * Use third order polynome y = ax^3 + bx^2 + cx + d
 * use x input in [0,1]
 * use condition f(0) = 0 => d = 0
 * use condition f(1) = 1 => a + b + c = 1
 * use a and b as variable parameters => adjust c = 1 - a - b
 */
template<class T>
class CNonLinearShaper
{
public:
    CNonLinearShaper()
        : m_A(0)
        , m_B(0)
        , m_C(1)
        , m_PreGain(1)
    {
    }

    void SetA(T A)
    {
        m_A = A;
        m_C = 1 - m_A - m_B;
    }

    void SetB(T B)
    {
        m_B = B;
        m_C = 1 - m_A - m_B;
    }

    void SetPregain(T PreGain)
    {
        m_PreGain = PreGain;
    }

    T operator()(T In) const
    {
        In = HardLimitUnsigned(m_PreGain * In);// limit to [0,1] !
        return HardLimitUnsigned(((m_A*In + m_B) * In + m_C)*In);
    }

private:
    T m_A;
    T m_B;
    T m_C;
    T m_PreGain;
};

#endif // NONLINEARSHAPER_H
