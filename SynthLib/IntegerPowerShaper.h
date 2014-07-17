#ifndef INTEGERPOWERSHAPER_H
#define INTEGERPOWERSHAPER_H

template <int N, class T>
constexpr T IntegerPower(const T& x)
{
    return N > 1 ? x*IntegerPower<(N-1)*(N > 1)>(x)
                 : N < 0 ? T(1)/IntegerPower<(-N)*(N < 0)>(x)
                         : N == 1 ? x
                                  : T(1);
}

template<class T>
inline constexpr T Powr(const T base, int const exponent)
{
    // (parentheses not required in next line)
    return (exponent == 0)     ? 1 :
           (exponent % 2 == 0) ? Powr(base, exponent/2)*Powr(base, exponent/2) :
                                 base * Powr(base, (exponent-1)/2) * Powr(base, (exponent-1)/2);
}

template<class T>
class CIntegerPowerShaper
{
public:
    CIntegerPowerShaper()
     : m_Strength(0)
     , m_Power(4)
     , m_PreGain(1)
    {}

    void SetStrength(T Strength)
    {
        m_Strength = Strength;
    }

    void SetPower(int Power)
    {
        m_Power = Power;
    }

    void SetPreGain(T PreGain)
    {
        m_PreGain = PreGain;
    }

    T operator()(T In)
    {
        T Dry = m_PreGain*In;
        T Wet = Dry<0 ? Powr(1+Dry, m_Power)-1 : 1-Powr(1-Dry, m_Power);
        return m_Strength*Wet + (1-m_Strength)*Dry;
    }

private:
    T m_Strength;
    int m_Power;
    T m_PreGain;
};


#endif // INTEGERPOWERSHAPER_H
