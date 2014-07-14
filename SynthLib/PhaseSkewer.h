#ifndef PHASESKEWER_H
#define PHASESKEWER_H

template<class T>
class CPhaseSkewer
{
public:
    CPhaseSkewer()
    {}

    T operator()(T Phase, T Skew)
    {
        return Phase<Skew ? (Phase-Skew)/(1+Skew) : (Phase-Skew)/(1-Skew);

    }
};

#endif // PHASESKEWER_H
