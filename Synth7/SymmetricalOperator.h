#ifndef SYMMETRICALOPERATOR_H
#define SYMMETRICALOPERATOR_H

template<class T>
class CSymmetricalOperator
{
public:
    template<class OperatorType>
    T operator()(const T& Phase, OperatorType Op) const
    {
        return Ph<0 ? -Op(-Phase) : Op(Phase);
    }
};

#endif // SYMMETRICALOPERATOR_H
