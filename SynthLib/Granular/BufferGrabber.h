#ifndef BUFFERGRABBER_H
#define BUFFERGRABBER_H

#include <vector>

template<class T>
class CBufferGrabber // bad name
{
public:
    typedef std::vector<T> BufferType;

    CBufferGrabber(int Capacity)
     : m_Capacity(Capacity)
     , m_Buffer(Capacity, 0)
     , m_Size(Capacity)
     , m_Grab(false)
     , m_Cntr(0)
    {}

    void SetSize(int Size)
    {
        if(0<= Size && Size<=m_Capacity)
        {
            m_Size = Size;
        }
    }

    void Grab()
    {
        m_Grab = true;
        m_Cntr = 0;
    }

    void operator()(T In)
    {
        if(m_Grab)
        {
            m_Buffer[m_Cntr] = In;

            ++m_Cntr;
            if(m_Size<=m_Cntr)
            {
                m_Grab = false;
            }
        }
    }

    int GetSize() const
    {
        return m_Size;
    }

    const BufferType& GetBuffer() const
    {
        return m_Buffer;
    }

private:
    const int m_Capacity;
    BufferType m_Buffer;
    int m_Size;
    bool m_Grab;
    int m_Cntr;
};

#endif // BUFFERGRABBER_H
