#ifndef LIMITER_H
#define LIMITER_H

/*!
 * Hard limiter class with variable min and max
 */
template<class T>
class CLimiter
{
public:
    CLimiter()
    {}

    T operator()(T In, T Min, T Max)
    {
        if(In<Min)
        {
            return Min;
        }
        if(Max<In)
        {
            return Max;
        }
        return In;
    }
};

/*
 * Hard limiter class with fixed min and max limits
 */
template<class T, int Min, int Max>
class CFixedLimiter
{
public:
    static constexpr T MinLimit = static_cast<T>(Min);
    static constexpr T MaxLimit = static_cast<T>(Max);

    CFixedLimiter()
    {}

    T operator()(T In)
    {
        if(In<MinLimit)
        {
            return MinLimit;
        }
        if(MaxLimit<In)
        {
            return MaxLimit;
        }
        return In;
    }
};

#endif // LIMITER_H
