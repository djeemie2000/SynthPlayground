#ifndef SYMMETRICALOPERATOR_H
#define SYMMETRICALOPERATOR_H

template<class T>
class CSymmetricalOperator
{
public:
    template<class OperatorType>
    T operator()(const T& Phase, OperatorType Op) const
    {
        return Phase<0 ? -Op(-Phase) : Op(Phase);
    }

    template<class OperatorType>
    T operator()(T Phase, OperatorType Op, T Mod) const
    {
        return Phase<0 ? -Op(-Phase, Mod) : Op(Phase, Mod);
    }
};

#endif // SYMMETRICALOPERATOR_H
