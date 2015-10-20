#ifndef LINEARINTERPOLATION_H
#define LINEARINTERPOLATION_H

// linear interpolation between (x1, y1) and (x2, y2)
template<class T>
T LinearInterpolation(T x1, T y1, T x2, T y2, T x)
{
    // (y-y1)/(x-x1) = (y2-y1)/(x2-x1)
    return y1 + (y2-y1)*(x-x1)/(x2-x1);
}

#endif // LINEARINTERPOLATION_H
