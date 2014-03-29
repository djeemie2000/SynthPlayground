#ifndef MIRROROPERATOR_H
#define MIRROROPERATOR_H

template<class T>
class CMirrorOperator
{
public:
    CMirrorOperator()
    {
    }

    template<class OperatorType>
    T operator()(const T& Phase, OperatorType& Operator)
    {
        return  Operator(1-Phase);
    }
};

#endif // MIRROROPERATOR_H
