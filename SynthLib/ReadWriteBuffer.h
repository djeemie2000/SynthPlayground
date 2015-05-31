#ifndef READWRITEBUFFER_H
#define READWRITEBUFFER_H

#include <vector>
#include <list>
#include <atomic>
#include <memory>
#include <algorithm>

/*!
 * Lock-free read/write buffer for one (!) reader and one (!) writer.
 * Use cases: write in filter, read in separate (slower) thread for gui, file io, ...
 */
template<class T>
class CReadWriteBuffer
{
public:
    CReadWriteBuffer(int BufferCapacity, int NumBuffers)
     : m_BufferCapacity(BufferCapacity)
     , m_NumBuffers(NumBuffers)
     , m_Buffers()
     , m_ReadIndex()
     , m_WriteIndex()
    {
        for(int idx = 0; idx<m_NumBuffers; ++idx)
        {
            m_Buffers.emplace_back( m_BufferCapacity );
        }
        m_ReadIndex = m_Buffers.begin();
        m_WriteIndex = m_Buffers.begin();
    }

    ~CReadWriteBuffer()
    {}

    int GetBufferCapacity() const
    {
        return m_BufferCapacity;
    }

    bool Read(std::vector<T>& DstBuffer)
    {
        bool Done = false;
        for(int idx = 0; !Done && idx<m_NumBuffers; ++idx)
        {
            if(m_ReadIndex->m_ReadWriteFlag==Readable)
            {
                DstBuffer.resize(m_ReadIndex->m_Buffer.size());
                std::copy(m_ReadIndex->m_Buffer.begin(), m_ReadIndex->m_Buffer.end(), DstBuffer.begin());
                m_ReadIndex->m_ReadWriteFlag = Writeable;
                Done = true;
            }
            ++m_ReadIndex;
            if(m_ReadIndex == m_Buffers.end())
            {
                m_ReadIndex = m_Buffers.begin();
            }
        }
        return Done;
    }

    bool Write(const T* SrcBuffer, int SrcBufferSize)
    {
        bool Done = false;
        for(int idx = 0; !Done && idx<m_NumBuffers; ++idx)
        {
            if(m_WriteIndex->m_ReadWriteFlag==Writeable)
            {
                // TODO check size vs buffer capacity, should not reallocate => only resize to size below buffer capacity
                m_WriteIndex->m_Buffer.resize(SrcBufferSize);
                std::copy(SrcBuffer, SrcBuffer+SrcBufferSize, m_WriteIndex->m_Buffer.data());
                m_WriteIndex->m_ReadWriteFlag = Readable;
                Done = true;
            }
            ++m_WriteIndex;
            if(m_WriteIndex == m_Buffers.end())
            {
                m_WriteIndex = m_Buffers.begin();
            }
        }
        return Done;
    }

private:
    static const bool Readable = false;
    static const bool Writeable = true;
    struct SBuffer
    {
        std::vector<T>  m_Buffer;
        std::atomic<bool> m_ReadWriteFlag;

        SBuffer(int BufferSize)
         : m_Buffer(BufferSize)
         , m_ReadWriteFlag()
        {
            m_ReadWriteFlag = Writeable;
        }
    };

    const int m_BufferCapacity;
    const int m_NumBuffers;
    std::list<SBuffer> m_Buffers;
    typename std::list<SBuffer>::iterator m_ReadIndex;
    typename std::list<SBuffer>::iterator m_WriteIndex;
};

#endif // READWRITEBUFFER_H

