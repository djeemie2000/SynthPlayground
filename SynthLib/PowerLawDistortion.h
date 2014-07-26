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
        m_Power = 1-Drive;
    }

    T operator()(T In)
    {
        // apply power in [0,1]
        // more distortion when power is near zero, no distortion if power is 1
        return 0<In ? std::pow(In, m_Power) : -std::pow(-In, m_Power);
        //return 2*std::pow((1+In)/2, m_Power)-1;//asymmetrical??
    }

private:
    T m_Power;
};

#endif // POWERLAWDISTORTION_H
