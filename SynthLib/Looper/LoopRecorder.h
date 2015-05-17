#ifndef LOOPRECORDER_H
#define LOOPRECORDER_H

#include <vector>
#include <Trigger.h>

template<class T>
class CLoopRecorder
{
public:
    typedef std::vector<T> BufferType;

    CLoopRecorder(int Capacity)
        : m_Capacity(Capacity)
        , m_Buffer(Capacity, 0)
        , m_Size(0)
        , m_Recording(true)
    {
    }

    int GetSize() const
    {
        return m_Size;
    }

    const T* GetData() const
    {
        return m_Buffer.data();
    }

    bool operator()(T Gate, T In)
    {
        if(CTriggerIn<float>::TriggerThreshold<Gate)
        {
            if(!m_Recording)
            {
                m_Size = 0;
                m_Recording = true;
            }
            if(m_Size<m_Capacity)
            {
                m_Buffer[m_Size++] = In;
                return true;//recording
            }
        }
        return false;//not recording
    }

private:
    const int m_Capacity;
    BufferType m_Buffer;
    int m_Size;
    bool m_Recording;
};

#endif // LOOPRECORDER_H

