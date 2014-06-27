#pragma once

#include <vector>

/*!
 * Using naive index based implementation
 */
template<class T>
class CDelayLine
{
public:
    CDelayLine(int Capacity, T DefaultValue)
        : m_Capacity(Capacity)
        , m_Values(Capacity, DefaultValue)
        , m_ReadIndex(0)
        , m_WriteIndex(0)
    {}

    void SetDelay(int Delay)
    {
        // Delay = std::max<Delay, m_Capacity); ???
        if(0<=Delay && Delay<m_Capacity)
        {
            // read index should be delay 'before' write index
            m_ReadIndex = Delay<m_WriteIndex ? m_WriteIndex-Delay : m_Capacity-(Delay-m_WriteIndex);//TODO check!
        }
    }

    T operator()()
    {
        return m_Values[m_ReadIndex];
    }

    T operator ()(T In)
    {
        m_Values[m_WriteIndex] = In;

        ++m_WriteIndex;
        if(m_Capacity<=m_WriteIndex)
        {
            m_WriteIndex = 0;
        }

        ++m_ReadIndex;
        if(m_Capacity<=m_ReadIndex)
        {
            m_ReadIndex = 0;
        }

        return m_Values[m_ReadIndex];
    }

private:
    const int m_Capacity;
    std::vector<T> m_Values;
    int m_ReadIndex;
    int m_WriteIndex;
};
