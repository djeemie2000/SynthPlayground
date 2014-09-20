#ifndef SAMPLEANDHOLD_H
#define SAMPLEANDHOLD_H

template<class T>
class CSampleAndHold
{
public:
    CSampleAndHold()
        : m_Out(0)
    {}

    T operator()(T In, bool Trigger)
    {
        if(Trigger)
        {
            m_Out = In;
        }
        return m_Out;
    }

private:
    T m_Out;
};

#endif // SAMPLEANDHOLD_H
