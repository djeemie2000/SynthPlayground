#ifndef INVSQUARE_H
#define INVSQUARE_H


template<class T>
class CInvSquare
{
public:
    T operator()(const T& Phase) const
    {
        return 1-Phase*Phase;
    }
};

#endif // INVSQUARE_H
