#ifndef ONEPOLEFILTER_H
#define ONEPOLEFILTER_H

#include <cstdlib>
#include <array>

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
        m_PrevOut = Out;//TODO more efficient?
        return Out;
    }

private:
    std::array<FilterType, N> m_Filter;
    int m_Stages;
    T m_Feedback;
    T m_PrevOut;

};

#endif // ONEPOLEFILTER_H
