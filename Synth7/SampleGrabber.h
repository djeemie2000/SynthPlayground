#pragma once

#include <vector>
#include <cmath>

template<class T>
class CSampleGrabber
{
public:
    typedef std::vector<T> SampleContainerType;

    CSampleGrabber()
        : m_Sample(), m_GrabSize(0), m_WriteIndex(0)
    {}

    void OnGrab(int GrabSize)
    {
        if(0<GrabSize)
        {
            m_GrabSize = GrabSize;
            m_Sample.assign(GrabSize, T());
            m_WriteIndex = 0;
        }
    }

    void OnRead(const T* Values, int Size)
    {
        if(Values && 0<Size && m_WriteIndex<m_GrabSize)
        {
            int GrabSize = std::min(Size, m_GrabSize-m_WriteIndex);
            std::copy(Values, Values+GrabSize, m_Sample.data()+m_WriteIndex);
            m_WriteIndex += GrabSize;
        }
    }

    bool IsSampled() const
    {
        return 0<m_GrabSize && m_GrabSize<=m_WriteIndex;
    }

    const SampleContainerType& GetSample() const
    {
        return m_Sample;
    }

private:
    SampleContainerType m_Sample;
    int m_GrabSize;
    int m_WriteIndex;

};



