#ifndef GRAINWINDOW_H
#define GRAINWINDOW_H

#include <cmath>

template<class T>
class CTriangularGrainWindow
{
public:
    CTriangularGrainWindow(){}

    T operator()(int Index, int GrainSize)
    {
        // an integer implementation of Triangle which can be rescaled to T in [0,1]
        return static_cast<T>( 2*Index<GrainSize ? 2*Index : 2*(GrainSize-Index))/static_cast<T>(GrainSize);
     }
};

template<class T>
class CPseudoSinGrainWindow
{
public:
    CPseudoSinGrainWindow(){}

    T operator()(int Index, int GrainSize)
    {
        // Phase should be in [0,1]
        // window should be in [0,1]
        // -> e.g. PseudoSin, Triangle,
        T Phase = static_cast<T>(Index)/static_cast<T>(GrainSize);
        return 4*Phase*(1-Phase);
    }
};
//TODO windows with short attack/decrease and sustain at 1

template<class T>
class CARGrainWindow
{
public:
    static const int Attack = 8;
    CARGrainWindow(){}

    T operator()(int Index, int GrainSize)
    {
        if(Index<Attack)
        {
            return static_cast<T>(Index)/Attack;
        }
        else if(GrainSize<=Index+Attack)
        {
            return static_cast<T>(GrainSize-Index)/Attack;
        }
        return 1;
    }
};

template<class T>
class CHammingGrainWindow
{
public:
    static constexpr T Alpha = static_cast<T>(0.54);
    static constexpr T Beta = static_cast<T>(0.46);
    static constexpr T TwoPi = static_cast<T>(6.283);

    CHammingGrainWindow(){}

    T operator()(int Index, int GrainSize)
    {
        return Alpha - Beta*std::cos((TwoPi*Index)/(GrainSize-1));
    }
};

#endif // GRAINWINDOW_H
