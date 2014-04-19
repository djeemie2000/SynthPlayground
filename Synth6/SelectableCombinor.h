#ifndef SELECTABLECOMBINOR_H
#define SELECTABLECOMBINOR_H

#include <vector>
#include <functional>

template<class T>
class CSelectableCombinor
{
public:
    CSelectableCombinor()
        : m_Current()
        , m_Operators()
    {
    }

    template<class CombinorType>
    void Add(CombinorType Op)
    {
        m_Operators.push_back( [Op](const T& In1, const T& In2){ return Op(In1, In2);} );
    }

    void Select(int Selected)
    {
        if(0<=Selected && Selected<m_Operators.size())
        {
            m_Current = m_Operators[Selected];
        }
    }

    float operator()(const T& In1, const T& In2)
    {
        return m_Current(In1, In2);
    }

private:
    typedef std::function<T(const T&, const T&)> CombinorWrapper;

    CombinorWrapper m_Current;
    std::vector<CombinorWrapper> m_Operators;
};

#endif // SELECTABLECOMBINOR_H
