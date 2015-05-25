#pragma once

#include <vector>

template<class T>
class CFilterBuffers
{
public:
    CFilterBuffers(const std::vector<T>& DefaultSourceBufferValues,
                   const std::vector<T>& DefaultDestinationBufferValues)
        : m_DefaultBufferSize(4096)
        , m_SourceBuffers()
        , m_DestinationBuffers()
    {
        for(T Default : DefaultSourceBufferValues)
        {
            m_DefaultSourceBuffers.push_back(std::vector<T>(m_DefaultBufferSize, Default));
        }
        for(T Default : DefaultDestinationBufferValues)
        {
            m_DefaultDestinationBuffers.push_back(std::vector<T>(m_DefaultBufferSize, Default));
        }
    }

    void Update(const std::vector<void*>& SourceBuffers,
                  const std::vector<void*>& DestinationBuffers,
                  int NumFrames)
    {
        m_SourceBuffers = SourceBuffers;
        m_DestinationBuffers = DestinationBuffers;
        if(m_DefaultBufferSize<NumFrames)
        {
            m_DefaultBufferSize = NumFrames;
            // resize all default buffers up to NumFrames
            for(auto& Buffer : m_DefaultSourceBuffers)
            {
                Buffer.resize(m_DefaultBufferSize, Buffer[0]);
            }
            for(auto& Buffer : m_DefaultDestinationBuffers)
            {
                Buffer.resize(m_DefaultBufferSize, Buffer[0]);
            }
        }
    }

    const T* GetSourceBuffer(int Idx) const
    {
        if(0<=Idx && Idx<m_DefaultSourceBuffers.size())
        {
            return (Idx<m_SourceBuffers.size() && m_SourceBuffers[Idx]) ? static_cast<const T*>(m_SourceBuffers[Idx]) : m_DefaultSourceBuffers[Idx].data();
        }
        return nullptr;
    }

    T* GetDestinationBuffer(int Idx)
    {
        if(0<=Idx && Idx<m_DefaultDestinationBuffers.size())
        {
            return (Idx<m_DestinationBuffers.size() && m_DestinationBuffers[Idx]) ? static_cast<T*>(m_DestinationBuffers[Idx]) : m_DefaultDestinationBuffers[Idx].data();
        }
        return nullptr;
    }

    bool GetSourceBufferConnected(int Idx) const
    {
        return (0<=Idx && Idx<m_SourceBuffers.size() && m_SourceBuffers[Idx]);
    }

    bool GetDestinationBufferConnection(int Idx) const
    {
        return (0<=Idx && Idx<m_DestinationBuffers.size() && m_DestinationBuffers[Idx]);
    }

private:
    int m_DefaultBufferSize;
    std::vector<std::vector<T>> m_DefaultSourceBuffers;
    std::vector<std::vector<T>> m_DefaultDestinationBuffers;

    std::vector<void*> m_SourceBuffers;
    std::vector<void*> m_DestinationBuffers;
};
