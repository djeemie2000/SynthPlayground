#ifndef LINSEGOPERATOR_H
#define LINSEGOPERATOR_H

template<class T>
class CLinSegOperator
{
public:
    CLinSegOperator(){}

    T operator()(T Phase, T Segment1Begin, T Segment1End, T Segment2Begin, T Segment2End) const
    {
        // assume Phase is in [-1, +1]
        return Phase<0 ? Segment1End + (Segment1End-Segment1Begin) * Phase
                       : Segment2Begin + (Segment2End-Segment2Begin) * Phase;
    }
};

#endif // LINSEGOPERATOR_H
