#ifndef COMBINOR_H
#define COMBINOR_H

#include <cmath>
#include <cstdlib>
#include "Conversions.h"

template<class T>
class CHardLimitAdder
{
public:
    CHardLimitAdder(){}

    T operator()(const T& In1, const T& In2) const
    {
        return HardLimitSigned(In1 + In2);// hard limited to 1
    }
};

template<class T>
class CMultiplier
{
public:
    CMultiplier(){}

    T operator()(const T& In1, const T& In2) const
    {
        return In1 * In2;
    }
};


template<class T>
class CDiffer
{
public:
    CDiffer(){}

    T operator()(const T& In1, const T& In2) const
    {
        return In1 - In2;
    }
};

template<class T>
class CMaxer
{
public:
    CMaxer(){}

    T operator()(const T& In1, const T& In2) const
    {
        return std::max(In1, In2);
    }
};

template<class T>
class CMiner
{
public:
    CMiner(){}

    T operator()(const T& In1, const T& In2) const
    {
        return std::min(In1, In2);
    }
};

template<class T>
class CDividerA
{
public:
    CDividerA(){}

    T operator()(const T& In1, const T& In2) const
    {
        return In1/(1+In2);
    }
};

template<class T>
class CDividerB
{
public:
    CDividerB(){}

    T operator()(const T& In1, const T& In2) const
    {
        return (1-In1)/(1+In2);
    }
};

#endif // COMBINOR_H
