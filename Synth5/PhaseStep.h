#pragma once

template<class T>
class CPhaseStep
{
public:
    CPhaseStep(const T& SamplingFrequency)
        : m_SamplingFrequency(SamplingFrequency)
        , m_PhaseStep(0)
    {}

    CPhaseStep()
        : m_SamplingFrequency(1)
        , m_PhaseStep(0)
    {}

    void SetFrequency(const T& Frequency)
    {
        m_PhaseStep = Frequency/m_SamplingFrequency;
    }

    T operator()()
    {
        return m_PhaseStep;
    }

private:
    T m_SamplingFrequency;
    T m_PhaseStep;
};
