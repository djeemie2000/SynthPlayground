#ifndef RAMPDOWN_H
#define RAMPDOWN_H

template<class T>
class CRampDown
{
public:
    T operator()(const T& Phase) const
    {
        return 1-Phase;
    }
};

#endif // RAMPDOWN_H
