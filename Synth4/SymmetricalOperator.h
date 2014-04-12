#ifndef SYMMETRICALOPERATOR_H
#define SYMMETRICALOPERATOR_H

template<class T>
class CSymmetricalOperator
{
public:
    template<class OperatorType>
    T operator()(const T& Phase, OperatorType Op) const
    {
        T Ph = 2*Phase - 1;
        T Out = Ph<0 ? -Op(-Ph) : Op(Ph);
        return (Out + 1)/2;
    }
};

#endif // SYMMETRICALOPERATOR_H
