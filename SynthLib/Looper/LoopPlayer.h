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

template<class T>
class CPlayerIndex
{
public:
    CPlayerIndex()
        : m_Index(0)
    {}

    void Sync()
    {
        m_Index = 0;
    }

    T operator()(T Speed)
    {
        m_Index += Speed;
        return m_Index;
    }

private:
    T m_Index;
};

template<class T>
class CBasicSingleShotPlayer
{
public:
    CBasicSingleShotPlayer()
    {}

    bool IsPlaying(int BufferSize, T Index) const
    {
        return static_cast<int>(Index)+1<BufferSize;
    }

    T operator()(const T* Buffer, int BufferSize, T Index)
    {
        if(IsPlaying(BufferSize, Index))
        {
            int IntegerIndex = Index;
            T Mix = Index - IntegerIndex;
            return (1-Mix)*Buffer[Index%BufferSize] + Mix*Buffer[(Index+1)%BufferSize];
        }

        return 0;
    }

    void operator()(const T* Buffer, int BufferSize, T Index, T& Out, bool& IsPlayng)
    {
        IsPlayng =  IsPlaying(BufferSize, Index);
        if(IsPlayng)
        {
            int IntegerIndex = Index;
            T Mix = Index - IntegerIndex;
            Out = (1-Mix)*Buffer[IntegerIndex] + Mix*Buffer[IntegerIndex+1];
        }
        else
        {
            Out = 0;
        }
    }

};


#endif // LOOPPLAYER_H
