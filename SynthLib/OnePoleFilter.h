#ifndef ONEPOLEFILTER_H
#define ONEPOLEFILTER_H

#include <cstdlib>
#include <array>
#include "Conversions.h"

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
        // parameter in [0,1] range
        // parameter is 1 => no filtering
        // parameter is 0 => lowest cutoff
        m_A0 = Parameter*Parameter;
        m_B1 = 1-Parameter*Parameter;
    }

    T operator()(T In)
    {
        T Out = m_A0*In + m_B1*m_PrevOut;
        m_PrevOut = Out;
        return Out;
    }

    T operator()(T In, T Parameter)
    {
        T Out = Parameter*Parameter*In + (1-Parameter*Parameter)*m_PrevOut;
        m_PrevOut = Out;
        return Out;
    }

private:
    T m_PrevOut;
    T m_A0;
    T m_B1;
};

template<class T, class FilterType, int N>
class CMultiStageFilter
{
public:
    CMultiStageFilter()
        : m_Filter()
        , m_Stages(1)
        , m_Feedback(0)
        , m_PrevOut(0)
    {
        m_Filter.fill(FilterType());
    }

    void SetStages(int Stages)
    {
        m_Stages = Stages;
    }

    void SetParameter(T Parameter)
    {
        for(auto& Filter : m_Filter)
        {
            Filter.SetParameter(Parameter);
        }
    }

    void SetFeedback(T Feedback)
    {
        // expected to be in [0,1]
        m_Feedback = Feedback;
    }

    T operator()(T In)
    {
        T Out = In - m_Feedback*m_PrevOut;
        int Stage = 0;
        while(Stage<m_Stages)
        {
            Out = m_Filter[Stage](Out);
            ++Stage;
        }
        m_PrevOut = HardLimitSigned(Out);//TODO more efficient?
        return m_PrevOut;
    }

    T operator()(T In, T Parameter)
    {
        T Out = In - m_Feedback*m_PrevOut;
        int Stage = 0;
        while(Stage<m_Stages)
        {
            Out = m_Filter[Stage](Out, Parameter);
            ++Stage;
        }
        m_PrevOut = HardLimitSigned(Out);//TODO more efficient?
        return m_PrevOut;
    }

private:
    std::array<FilterType, N> m_Filter;
    int m_Stages;
    T m_Feedback;
    T m_PrevOut;

};

#endif // ONEPOLEFILTER_H
