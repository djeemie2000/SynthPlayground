#ifndef TRIANGLE_H
#define TRIANGLE_H

template<class T>
class CTriangle
{
public:
    CTriangle(){}
    T operator()(const T& Phase) const
    {
        return Phase<0.5 ? 2*Phase : 2*(1-Phase);
    }
};

#endif // TRIANGLE_H
