#ifndef ONEVOLTPEROCTAVE_H
#define ONEVOLTPEROCTAVE_H

#include <cmath>

/*
 * Converts 1V/Oct signal to frequency
 */
template<class T>
class COneVoltPerOctave
{
public:
    static constexpr T Base = static_cast<T>(2);

    COneVoltPerOctave(T Frequency0)
        : m_Frequency0(Frequency0)
    {}

    T operator()(T CV)
    {
        // 0 CV => f = 1*f0
        // 1 CV => f = 2*f0
        // 2 CV => f = 4*f0
        // 3 CV => f = 8*f0
        //
        // 0.5 CV => f = sqrt(2)*f0
        // 1.5 CV => f = 2*sqrt(2)*f0
        // ...
        return m_Frequency0*std::pow(Base, CV);
    }

private:
    T m_Frequency0; //!< frequency corresponding to zero CV signal
};

#endif // ONEVOLTPEROCTAVE_H
