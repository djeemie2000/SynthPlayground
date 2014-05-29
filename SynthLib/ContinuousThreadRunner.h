#ifndef CONTINUOUSTHREADRUNNER_H
#define CONTINUOUSTHREADRUNNER_H

#include <atomic>
#include <thread>

template<class RunnableType>
class CContinuousThreadRunner
{
public:
    CContinuousThreadRunner(RunnableType& Runnable)
        : m_Stop(true)
        , m_Thread()
        , m_Runnable(Runnable)
    {}

    ~CContinuousThreadRunner()
    {
        Stop();
    }

    void Start()
    {
        Stop();
        m_Stop = false;
        m_Thread = std::thread( [this]
        {
            while(!m_Stop)
            {
                m_Runnable.OnTick();
            }
        } );
    }

    void Stop()
    {
        m_Stop = true;
        if(m_Thread.joinable())
        {
            m_Thread.join();
        }
    }

private:
    std::atomic<bool> m_Stop;
    std::thread m_Thread;
    RunnableType& m_Runnable;
};

#endif // CONTINUOUSTHREADRUNNER_H
