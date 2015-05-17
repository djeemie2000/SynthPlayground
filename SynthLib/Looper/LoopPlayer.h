#ifndef LOOPPLAYER_H
#define LOOPPLAYER_H

template<class T>
class CLoopPlayer
{
public:
    CLoopPlayer()
     : m_Index(0)
    {}

    void Sync()
    {
        m_Index = 0;
    }

    T operator()(const T* Buffer, int BufferSize, T PlaybackSpeed)
    {
        m_Index += PlaybackSpeed;
        if(BufferSize<m_Index)
        {
            m_Index = 0;//TODO???
        }

        // interpolation
        int Index = m_Index;
        T Mix = m_Index - Index;
        return (1-Mix)*Buffer[Index%BufferSize] + Mix*Buffer[(Index+1)%BufferSize];
    }

private:
    T m_Index;
};

#endif // LOOPPLAYER_H
