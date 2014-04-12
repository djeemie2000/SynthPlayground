#ifndef FLIPOPERATOR_H
#define FLIPOPERATOR_H

template<class T>
class CFlipOperator
{
public:
    CFlipOperator()
    {
    }

    template<class OperatorType>
    T operator()(const T& Phase, OperatorType& Operator)
    {
        return  1-Operator(Phase);
    }

    template<class OperatorType>
    T operator()(const T& Phase, OperatorType& Operator, bool Apply)
    {
        return  Apply ? 1-Operator(Phase) : Operator(Phase);
    }
};

#endif // FLIPOPERATOR_H
