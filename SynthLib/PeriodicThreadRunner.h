#ifndef PERIODICTHREADRUNNER_H
#define PERIODICTHREADRUNNER_H

#include <atomic>
#include <thread>
#include <chrono>

template<class RunnableType>
class CPeriodicThreadRunner
{
public:
    CPeriodicThreadRunner(RunnableType& Runnable)
        : m_Stop(true)
        , m_PeriodMilliSeconds(1)
        , m_Thread()
        , m_Runnable(Runnable)
    {}

    ~CPeriodicThreadRunner()
    {
        Stop();
    }

    void SetPeriod(int PeriodMilliSeconds)
    {
        m_PeriodMilliSeconds = PeriodMilliSeconds;
    }

    void Start()
    {
        Stop();
        m_Stop = false;
        m_Thread = std::thread( [this]
        {
            while(!m_Stop)
            {
                std::chrono::milliseconds Duration(m_PeriodMilliSeconds);
                auto NextTime = std::chrono::steady_clock::now() + Duration;
                m_Runnable.OnTick();
                std::this_thread::sleep_until(NextTime);
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
    std::atomic<int> m_PeriodMilliSeconds;
    std::thread m_Thread;
    RunnableType& m_Runnable;
};

#endif // PERIODICTHREADRUNNER_H
