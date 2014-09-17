#ifndef GATE_H
#define GATE_H

#include <cmath>

template<class T>
class CGate
{
public:
    CGate()
     : m_Threshold(0)
    {}

    void SetThreshold(T Threshold)
    {
        m_Threshold = Threshold;
    }

    T operator()(T In)
    {
        return m_Threshold < std::abs(In) ? In : 0;
    }

private:
    T m_Threshold;
};

#endif // GATE_H
