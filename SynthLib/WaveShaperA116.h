#pragma once

#include <cstdlib>
#include <array>

template<class T>
class CWaveShaperA116
{
public:    
    CWaveShaperA116()
    {}


    T operator()(T In, T LowTh, T HighTh, T Symmetry)
    {
        // In, LowTh, HighTh in [-1,1]
        // Symmetry in [-1,1]
        T Offset = (HighTh + LowTh)/2;
        return Clip(In, LowTh, HighTh) + Symmetry*In - Offset;
    }

private:
    T Clip(T In, T LowTh, T HighTh)
    {
        T Out = LowTh<In ? In : LowTh;
        Out = Out<HighTh ? Out : HighTh;
        return Out;
    }
};
