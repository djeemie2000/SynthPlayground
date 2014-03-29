#ifndef FULLPSEUDOSIN_H
#define FULLPSEUDOSIN_H

#include "PseudoSin.h"

template<class T>
class CFullPseudoSin
{
public:
    T operator()(const T& Phase)
    {
        // Phase<0.5 => 0.5 + 0.5 * PseudoSin(2*Phase)      = 0.5 * ( 1 + PseudoSin(2*Phase) )
        // Phase>0.5 => 0.5 - 0.5 * PseudoSin(2*(Phase-0.5)) = 0.5 * (1 - PseudoSin(2*Phase-1) )
        return Phase<0.5f  ? 0.5f * (1 + CPseudoSin<T>()(2*Phase)) : 0.5f * (1 - CPseudoSin<T>()(2*Phase-1));//TODO
    }
};

#endif // FULLPSEUDOSIN_H
