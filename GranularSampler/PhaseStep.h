#pragma once

template<class T>
class CPhaseStep
{
public:
    CPhaseStep(const T& SamplingFrequency)
        : m_SamplingFrequency(SamplingFrequency)
        , m_PhaseStep(0)
    {}

    void SetFrequency(const T& Frequency)
    {
        m_PhaseStep = m_SamplingFrequency/Frequency;
    }

    T operator()()
    {
        return m_PhaseStep;
    }

private:
    T m_SamplingFrequency;
    T m_PhaseStep;
};
