#ifndef WAVEFOLDER_H
#define WAVEFOLDER_H

#include <cmath>

template<class T>
class CWaveFold1
{
public:
    CWaveFold1()
        : m_Fold(1)
    {}

    void SetFold(const T& Fold)
    {
        m_Fold = Fold;
    }

    T operator()(const T& In)
    {
        // In in [0, 1]
        T Out = In/m_Fold;

        while(1<Out)
        {
            Out -= 1;
        }

        return Out;
    }

private:
    T m_Fold;
};

template<class T>
class CWaveFold2
{
public:
    CWaveFold2()
        : m_Fold(1)
    {}

    void SetFold(const T& Fold)
    {
        m_Fold = Fold;
    }

    T operator()(const T& In)
    {
        // In in [0, 1]
        T Out = In/m_Fold;

        bool Done = false;
        while(!Done)
        {
            if(Out<1)
            {
                Done = true;
            }
            else if(Out<2)
            {
                Out = 2 - Out;
                Done = true;
            }
            else
            {
                Out -= 2;
            }
        }

        return Out;
    }

    T operator()(T In, T Fold)
    {
        if(Fold<=0)
        {
            return 0;
        }

        // In in [0, 1]
        T Out = In/Fold;

        bool Done = false;
        while(!Done)
        {
            if(Out<1)
            {
                Done = true;
            }
            else if(Out<2)
            {
                Out = 2 - Out;
                Done = true;
            }
            else
            {
                Out -= 2;
            }
        }

        return Out;
    }

private:
    T m_Fold;
};

#endif // WAVEFOLDER_H
