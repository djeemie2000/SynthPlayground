#ifndef GRAINTRIGGER_H
#define GRAINTRIGGER_H

class CDensityGrainTrigger
{
public:
    CDensityGrainTrigger()
     : m_Cntr(1<<30)//trigger at initial call, provided density is smaller
    {}

    void Sync()
    {
        m_Cntr = 1<<30;//trigger at initial call, provided density is smaller
    }

    bool operator()(int Density)
    {
        if(m_Cntr<Density)
        {
            ++m_Cntr;
            return false;
        }

        m_Cntr = 1;
        return true;
    }

private:
    int m_Cntr;
};

#endif // GRAINTRIGGER_H
