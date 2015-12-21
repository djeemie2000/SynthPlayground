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

template<class T, int Scale, int StrengthScale>
T IntModulatedAdd(T Carrier, T Modulator, T Strength)
{
    T Mod = (Strength * Modulator) >> StrengthScale;
    return (Carrier + Mod) >> 1;
}

template<class T, int Scale, int StrengthScale>
T IntModulatedHardLimitAdd(T Carrier, T Modulator, T Strength)
{
    T Mod = (Strength * Modulator) >> StrengthScale;
    return IntHardLimitBipolar<T, Scale>(Carrier + Mod);// hard limited to +/- 2^Scale-1
}

template<class T, int Scale, int StrengthScale>
T IntModulatedMult(T Carrier, T Modulator, T Strength)
{
    // this in fact is amplitude modulation
    // as opposed to ring modulation below
    T Mod = Interpolate<T, StrengthScale>(Modulator, IntMaxSigned<Scale>(), Strength);
    return ( Carrier * Mod ) >> (Scale-1);//assumes signed integer in [-2^Scale-1, 2^Scale-1]
}

//template<class T, int Scale, int StrengthScale>
//T IntMultUnipolar(T Carrier, T Modulator, T Strength)
//{
//    return IntUnipolarToBipolar<Scale>( IntMult<T, Scale>(IntBipolarToUnipolar<Scale>(Carrier), IntBipolarToUnipolar<Scale>(Modulator)) );
//}

//template<class T, int Scale, int StrengthScale>
//T IntMultAbs(T Carrier, T Modulator, T Strength)
//{
//    return IntUnipolarToBipolar<Scale>( IntMult<T, Scale>(abs(Carrier), abs(Modulator)) );
//}

template<class T, int Scale, int StrengthScale>
T IntMultFirst(T Carrier, T Modulator, T Strength)
{
    T Mod = Interpolate<T, StrengthScale>(Modulator, IntMaxSigned<Scale>(), Strength);
    return ( Carrier * abs(Mod) ) >> (Scale-1);
}

//template<class T, int Scale, int StrengthScale>
//T IntMultSecond(T Carrier, T Modulator, T Strength)
//{
//    return ( abs(Carrier) * Modulator ) >> (Scale-1);
//}

//template<class T, int Scale, int StrengthScale>
//T IntRingModFirst(T Carrier, T Modulator, T Strength)
//{
//    // Modulator is converted from [-1, 1] to [0,1] and serves as amplitude modulator of Carrier
//    //return Carrier * (1 + Modulator) / 2;
//    return ( Carrier * IntBipolarToUnipolar<Scale>(Modulator) ) >> (Scale-1);
//}

//template<class T, int Scale, int StrengthScale>
//T IntRingModSecond(T Carrier, T Modulator, T Strength)
//{
//    // Carrier is converted from [-1, 1] to [0,1] and serves as amplitude modulator of Modulator
//    //return Modulator * (1 + Carrier) / 2;
//    return (Modulator * IntBipolarToUnipolar<Scale>(Carrier)) >> (Scale-1);
//}

template<class T, int Scale, int StrengthScale>
T IntModulatedHardLimitDiff(T Carrier, T Modulator, T Strength)
{
    T Mod = (Strength * Modulator) >> StrengthScale;
    return IntHardLimitBipolar<T, Scale>(Carrier - Mod);
}

//template<class T, int Scale, int StrengthScale>
//T IntDiffAbs(T Carrier, T Modulator, T Strength)
//{
//    return abs(Carrier) - abs(Modulator);
//}


//template<class T, int Scale, int StrengthScale>
//T IntMax(T Carrier, T Modulator, T Strength)
//{
//    return max(Carrier, Modulator);
//}

//template<class T, int Scale, int StrengthScale>
//T IntMaxAbs(T Carrier, T Modulator, T Strength)
//{
//    // return the value with the biggest abs
//    return abs(Carrier) < abs(Modulator) ? Modulator : Carrier;
//}

//template<class T, int Scale, int StrengthScale>
//T IntMinAbs(T Carrier, T Modulator, T Strength)
//{
//    // return the value with the smallest abs
//    return abs(Carrier) < abs(Modulator) ? Carrier : Modulator;
//}

//template<class T, int Scale, int StrengthScale>
//T IntMin(T Carrier, T Modulator, T Strength)
//{
//    return min(Carrier, Modulator);
//}

//template<class T, int Scale, int StrengthScale>
//T IntMinAbsFirst(T Carrier, T Modulator, T Strength)
//{
//    return min(abs(Carrier), Modulator);
//}

//template<class T, int Scale, int StrengthScale>
//T IntMinAbsSecond(T Carrier, T Modulator, T Strength)
//{
//    return min(Carrier, abs(Modulator));
//}

//template<class T, int Scale, int StrengthScale>
//T IntPosNegAdd(T Carrier, T Modulator, T Strength)
//{
//    // add the positive part of Carrier and the negative part of Modulator
//    return max(Carrier,static_cast<T>(0)) + min(Modulator, static_cast<T>(0));
//}

//template<class T, int Scale, int StrengthScale>
//T IntNegPosAdd(T Carrier, T Modulator, T Strength)
//{
//    // add the positive part of Modulator and the negative part of Carrier
//    return min(Carrier,static_cast<T>(0)) + max(Modulator, static_cast<T>(0));
//}

//template<class T, int Scale, int StrengthScale>
//T IntMultMod1(T Carrier, T Modulator, T Strength)
//{
//    // return Carrier*(1+Modulator);
//    return ( Carrier * ( (1<<(Scale-1)) + Modulator ) ) >> (Scale);
//}

//template<class T, int Scale, int StrengthScale>
//T IntMultMod2(T Carrier, T Modulator, T Strength)
//{
//    //return Modulator*(1+Carrier);
//    return ( Modulator * ( (1<<(Scale-1)) + Carrier ) ) >> (Scale);
//}

}//namespace isl
