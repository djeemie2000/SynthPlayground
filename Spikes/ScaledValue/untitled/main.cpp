#include <iostream>

using namespace std;

template<class T>
class CScaledValue
{
public:
    CScaledValue(T Value, int Scale)
        : m_Value(Value)
        , m_Scale(Scale)
    {}

//    T operator*(T Other)
//    {
//        return (Other*m_Value)>>m_Scale;
//    }

    operator T() const
    {
        return m_Value >> m_Scale;
    }

    T Value() const { return m_Value; }
    int Scale() const { return m_Scale; }

private:
    T m_Value;
    int m_Scale;
};

template<class T, class U>
T operator*(U Val1, const CScaledValue<T>& Val2)
{
    return (Val1*Val2.Value())>>Val2.Scale();
}

template<class T, class U>
T operator*(const CScaledValue<T>& Val2, U Val1)
{
    return (Val1*Val2.Value())>>Val2.Scale();
}

template<class T>
CScaledValue<T> operator*(const CScaledValue<T>& Val1, const CScaledValue<T>& Val2)
{
    return CScaledValue<T>(Val1.Value()*Val2.Value(), Val1.Scale()+Val2.Scale());
}


int main()
{
    cout << "Hello World!" << endl;

    CScaledValue<int> Val(256+128, 8);

    int Result = Val*2;
    std::cout << Result << std::endl;

    long Result2 = 2*Val;
    std::cout << Result2 << std::endl;

    CScaledValue<int> Result3 = Val*Val;
    int Tmp = Result3;
    std::cout << Tmp << std::endl;

    return 0;
}
