#ifndef POWERLAWDISTORTION_H
#define POWERLAWDISTORTION_H

#include <cmath>

template<class T>
class CPowerLawDistortion
{
public:
    CPowerLawDistortion()
     : m_Power(1)
    {}

    void SetDrive(T Drive)
    {
        // assume drive in [0,1]
        m_Power = 1-Drive;
    }

    T operator()(T In)
    {
        // apply power in [0,1]
        // more distortion when power is near zero, no distortion if power is 1
        return 0<In ? std::pow(In, m_Power) : -std::pow(-In, m_Power);
        //return 2*std::pow((1+In)/2, m_Power)-1;//asymmetrical???
    }

    T operator()(T In, T Drive)
    {
        T Power = 1-Drive;
        return 0<In ? std::pow(In, Power) : -std::pow(-In, Power);
    }

private:
    T m_Power;
};

#endif // POWERLAWDISTORTION_H
