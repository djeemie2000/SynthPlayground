#ifndef PSEUDOSIN_H
#define PSEUDOSIN_H

template<class T>
class CPseudoSin
{
public:
    T operator()(const T& Phase) const
    {
        //   1-(1-2*Phase)*(1-2*Phase)
        // = 1-( 1 - 2*Phase -2*Phase + 4*Phase*Phase )
        // = 1-( 1 -4*Phase + 4*Phase*Phase)
        // = 4*Phase - 4*Phase*Phase
        // = 4*Phase*(1-Phase)
        //
        return 4*Phase*(1-Phase);
    }
};

#endif // PSEUDOSIN_H
