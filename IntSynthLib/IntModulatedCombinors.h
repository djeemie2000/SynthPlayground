#pragma once

#include <cmath>
#include "IntOperators.h"
#include "IntCombinors.h"
#include "IntUtilities.h"

namespace isl
{

using std::max;
using std::min;

typedef int(*IntModulatedCombinor)(int, int, int);

// C+M
template<class T, int Scale, int StrengthScale>
T IntModulatedAdd(T Carrier, T Modulator, T Strength)
{
    T Mod = (Strength * Modulator) >> StrengthScale;
    return (Carrier + Mod) >> 1;
}

// L(C+M)
template<class T, int Scale, int StrengthScale>
T IntModulatedHardLimitAdd(T Carrier, T Modulator, T Strength)
{
    T Mod = (Strength * Modulator) >> StrengthScale;
    return IntHardLimitBipolar<T, Scale>(Carrier + Mod);// hard limited to +/- 2^Scale-1
}

// C*M
template<class T, int Scale, int StrengthScale>
T IntModulatedMult(T Carrier, T Modulator, T Strength)
{
    // this in fact is amplitude modulation
    // as opposed to ring modulation below
    T Mod = Interpolate<T, StrengthScale>(Modulator, IntMaxSigned<Scale>(), Strength);
    return ( Carrier * Mod ) >> (Scale-1);//assumes signed integer in [-2^Scale-1, 2^Scale-1]
}

// UC*UM
template<class T, int Scale, int StrengthScale>
T IntModulatedMultUnipolar(T Carrier, T Modulator, T Strength)
{
    T Mod = Interpolate<T, StrengthScale>(Modulator, IntMaxSigned<Scale>(), Strength);
    return IntUnipolarToBipolar<Scale>( IntMult<T, Scale>(IntBipolarToUnipolar<Scale>(Carrier), IntBipolarToUnipolar<Scale>(Mod)) );
}

// |C|*|M|
template<class T, int Scale, int StrengthScale>
T IntModulatedMultAbs(T Carrier, T Modulator, T Strength)
{
    T Mod = Interpolate<T, StrengthScale>(abs(Modulator), IntMaxSigned<Scale>(), Strength);
    T Carr = Interpolate<T, StrengthScale>(Carrier>>1, abs(Carrier), Strength);
    return IntUnipolarToBipolar<Scale>( IntMult<T, Scale>(Carr, Mod) );
}

// C*|M|
template<class T, int Scale, int StrengthScale>
T IntModulatedMultFirst(T Carrier, T Modulator, T Strength)
{
    T Mod = Interpolate<T, StrengthScale>(Modulator, IntMaxSigned<Scale>(), Strength);
    return ( Carrier * abs(Mod) ) >> (Scale-1);
}

// C*UM
template<class T, int Scale, int StrengthScale>
T IntModulatedRingModFirst(T Carrier, T Modulator, T Strength)
{
    // Modulator is converted from [-1, 1] to [0,1] and serves as amplitude modulator of Carrier
    //return Carrier * (1 + Modulator) / 2;
    T Mod = (Strength * Modulator) >> StrengthScale;
    return ( Carrier * IntBipolarToUnipolar<Scale>(Mod) ) >> (Scale-1);
}

// L(C-M)
template<class T, int Scale, int StrengthScale>
T IntModulatedHardLimitDiff(T Carrier, T Modulator, T Strength)
{
    T Mod = (Strength * Modulator) >> StrengthScale;
    return IntHardLimitBipolar<T, Scale>(Carrier - Mod);
}

// |C|-|M|
template<class T, int Scale, int StrengthScale>
T IntModulatedDiffAbs(T Carrier, T Modulator, T Strength)
{
    //T Mod = (Strength * Modulator) >> StrengthScale;
    //T Carr = Interpolate<T, StrengthScale>(Carrier, abs(Carrier), Strength);
    //return Carr - abs(Mod);
    T Mod = abs(Carrier)-abs(Modulator);
    return Interpolate<T, StrengthScale>(Carrier, Mod, Strength);
}

// M
template<class T, int Scale, int StrengthScale>
T IntModulatedMax(T Carrier, T Modulator, T Strength)
{
    T Mod = Interpolate<T, StrengthScale>(Modulator, IntMinSigned<Scale>(), Strength);
    return max(Carrier, Mod);
}

// M||
template<class T, int Scale, int StrengthScale>
T IntModulatedMaxAbs(T Carrier, T Modulator, T Strength)
{
    // return the value with the biggest abs
    T Mod = (Strength * Modulator) >> StrengthScale;
    return abs(Mod) < abs(Carrier) ? Carrier : Modulator;
}

// m||
template<class T, int Scale, int StrengthScale>
T IntModulatedMinAbs(T Carrier, T Modulator, T Strength)
{
    // return the value with the smallest abs
    T Mod = Interpolate<T, StrengthScale>(Modulator, IntMinSigned<Scale>(), Strength);
    return abs(Carrier) < abs(Mod) ? Carrier : Modulator;
}

// m
template<class T, int Scale, int StrengthScale>
T IntModulatedMin(T Carrier, T Modulator, T Strength)
{
    T Mod = Interpolate<T, StrengthScale>(Modulator, IntMaxSigned<Scale>(), Strength);
    return min(Carrier, Mod);
}

// mC|M|
template<class T, int Scale, int StrengthScale>
T IntModulatedMinAbsSecond(T Carrier, T Modulator, T Strength)
{
    T Mod = Interpolate<T, StrengthScale>(Modulator, IntMaxSigned<Scale>(), Strength);
    return min(Carrier, abs(Mod));
}

// MC|M|
template<class T, int Scale, int StrengthScale>
T IntModulatedMaxAbsSecond(T Carrier, T Modulator, T Strength)
{
    T Mod = Interpolate<T, StrengthScale>(Modulator, IntMinSigned<Scale>(), Strength);
    return max(Carrier, abs(Mod));
}

// C(1+M)
template<class T, int Scale, int StrengthScale>
T IntModulatedMultMod1(T Carrier, T Modulator, T Strength)
{
    // return Carrier*(1+Modulator);
    T Mod = (Strength * Modulator) >> StrengthScale;
    return ( Carrier * ( (1<<(Scale-1)) + Mod ) ) >> (Scale);
}

}//namespace isl
