#ifndef CONSTNUMSAMPLESGENERATOR_H
#define CONSTNUMSAMPLESGENERATOR_H

template<class T>
class CConstNumSamplesGenerator
{
public:
    CConstNumSamplesGenerator(T SamplingFrequency)
        : m_SamplingFrequency(SamplingFrequency)
        , m_Value(0)
    {}

    void SetMilliSeconds(T MilliSeconds)
    {
        m_Value = MilliSeconds*m_SamplingFrequency/1000;
    }

    T operator()()
    {
        return m_Value;
    }

private:
    T m_SamplingFrequency;
    T m_Value;
};

#endif // CONSTNUMSAMPLESGENERATOR_H
