#ifndef ONEPOLEFILTER_H
#define ONEPOLEFILTER_H

template<class T>
class COnePoleLowPassFilter
{
public:
    COnePoleLowPassFilter()
        : m_PrevOut(0)
        , m_A0(1)
        , m_B1(0)
    {}

    void SetParameter(T Parameter)
    {
        m_A0 = 1-Parameter;
        m_B1 = Parameter;
    }

    T operator()(T In)
    {
        T Out = m_A0*In + m_B1*m_PrevOut;
        m_PrevOut = Out;
        return Out;
    }

    T operator()(T In, int Repeat)
    {
        T Out = operator()(In);
        while(1<Repeat)
        {
            Out = operator()(Out);
            --Repeat;
        }
        return Out;
    }


private:
    T m_PrevOut;
    T m_A0;
    T m_B1;
};


#endif // ONEPOLEFILTER_H
