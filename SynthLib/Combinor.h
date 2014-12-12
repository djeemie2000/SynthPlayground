#ifndef COMBINOR_H
#define COMBINOR_H

#include <cmath>
#include <cstdlib>
#include "Conversions.h"

template<class T>
class CHardLimitAdd
{
public:
    CHardLimitAdd(){}

    T operator()(const T& In1, const T& In2) const
    {
        return HardLimitSigned(In1 + In2);// hard limited to 1
    }
};

template<class T>
class CMult
{
public:
    CMult(){}

    T operator()(const T& In1, const T& In2) const
    {
        // this in fact is amplitude modulation
        // as opposed to ring modulation below
        return In1 * In2;
    }
};

template<class T>
class CMultFirst
{
public:
    CMultFirst(){}

    T operator()(const T& In1, const T& In2) const
    {
        return In1 * std::abs(In2);
    }
};

template<class T>
class CMultSecond
{
public:
    CMultSecond(){}

    T operator()(const T& In1, const T& In2) const
    {
        return std::abs(In1) * In2;
    }
};

template<class T>
class CRingModFirst
{
public:
    CRingModFirst(){}

    T operator()(const T& In1, const T& In2) const
    {
        // In2 is converted from [-1, 1] to [0,1] and serves as amplitude modulator of In1
        return In1 * (1 + In2) / 2;
    }
};

template<class T>
class CRingModSecond
{
public:
    CRingModSecond(){}

    T operator()(const T& In1, const T& In2) const
    {
        // In1 is converted from [-1, 1] to [0,1] and serves as amplitude modulator of In2
        return In2 * (1 + In1) / 2;
    }
};

template<class T>
class CHardLimitDiff
{
public:
    CHardLimitDiff(){}

    T operator()(const T& In1, const T& In2) const
    {
        return HardLimitSigned(In1 - In2);
    }
};

template<class T>
class CDiffAbs
{
public:
    CDiffAbs(){}

    T operator()(const T& In1, const T& In2) const
    {
        return std::abs(In1) - std::abs(In2);
    }
};


template<class T>
class CMax
{
public:
    CMax(){}

    T operator()(const T& In1, const T& In2) const
    {
        return std::max(In1, In2);
    }
};

template<class T>
class CMaxAbs
{
public:
    CMaxAbs(){}

    T operator()(const T& In1, const T& In2) const
    {
        // return the value with the biggest abs
        return std::abs(In1) < std::abs(In2) ? In2 : In1;
    }
};

template<class T>
class CMinAbs
{
public:
    CMinAbs(){}

    T operator()(const T& In1, const T& In2) const
    {
        // return the value with the smallest abs
        return std::abs(In1) < std::abs(In2) ? In1 : In2;
    }
};

template<class T>
class CMin
{
public:
    CMin(){}

    T operator()(const T& In1, const T& In2) const
    {
        return std::min(In1, In2);
    }
};

template<class T>
class CPosNegAdd
{
public:
    CPosNegAdd(){}

    T operator()(const T& In1, const T& In2) const
    {
        // add the positive part of In1 and the negative part of In2
        return std::max(In1,static_cast<T>(0)) + std::min(In2, static_cast<T>(0));
    }
};

template<class T>
class CNegPosAdd
{
public:
    CNegPosAdd(){}

    T operator()(const T& In1, const T& In2) const
    {
        // add the positive part of In2 and the negative part of In1
        return std::min(In1,static_cast<T>(0)) + std::max(In2, static_cast<T>(0));
    }
};

template<class T>
class CMultMod1
{
public:
    CMultMod1(){}

    T operator()(const T& In1, const T& In2) const
    {
//        return In1*(1+In2);
        return In1 + In1*In2;
    }
};

template<class T>
class CMultMod2
{
public:
    CMultMod2(){}

    T operator()(const T& In1, const T& In2) const
    {
//        return In2*(1+In1);
        return In2 + In2*In1;
    }
};

template<class T>
class CDividerA
{
public:
    CDividerA(){}

    T operator()(const T& In1, const T& In2) const
    {
        return In1/(2+In2);
    }
};

template<class T>
class CDividerB
{
public:
    CDividerB(){}

    T operator()(const T& In1, const T& In2) const
    {
        return In1/(2-In2);
    }
};

template<class T>
class CDividerC
{
public:
    CDividerC(){}

    T operator()(const T& In1, const T& In2) const
    {
        return In1/(1+std::abs(In2));
    }
};

#endif // COMBINOR_H
