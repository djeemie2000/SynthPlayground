#pragma once

template<class T>
class CConstGenerator
{
public:
    CConstGenerator()
        : m_Value(0)
    {}

    void Set(const T& Value)
    {
        m_Value = Value;
    }

    T operator()()
    {
        return m_Value;
    }

private:
    T m_Value;
};
