#ifndef SELECTABLEOPERATOR_H
#define SELECTABLEOPERATOR_H

#include <vector>
#include <functional>
#include "NoOp.h"


template<class T>
class CSelectableOperator
{
public:
    CSelectableOperator()
        : m_Current()
        , m_Operators()
    {
    }

    template<class OperatorType>
    void Add(OperatorType Op)
    {
        m_Operators.push_back( [Op](const T& Phase){ return Op(Phase);} );
    }

    void Select(int Selected)
    {
        if(0<=Selected && Selected<m_Operators.size())
        {
            m_Current = m_Operators[Selected];
        }
    }

//    template<class OperatorType>
//    void Set(const OperatorType& Op)
//    {
//        m_Current = [Op](const T& Phase){ return Op(Phase);} ;
//    }

    float operator()(const T& Phase)
    {
        return m_Current(Phase);
    }

private:
    typedef std::function<T(const T&)> OperatorWrapper;

    OperatorWrapper m_Current;
    std::vector<OperatorWrapper> m_Operators;
};

#endif // SELECTABLEOPERATOR_H
