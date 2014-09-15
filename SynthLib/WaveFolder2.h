#ifndef WAVEFOLDER2_H
#define WAVEFOLDER2_H

#include <array>
#include "SymmetricalOperator.h"

template<class T>
class CWaveFolderStage
{
public:
    CWaveFolderStage(){}

    T operator()(T In, T Fold)
    {
        // assume In in [0,1]
        // assume Fold in [0,1]
        // Fold = 0 => Out = In, fold = 1 => maximum fold
        // => can achieve maximally 1 fold
        T Temp = In*(1+Fold);
        return 1<Temp ? 2-Temp : Temp;
    }
};

template<class T>
class CMultiStageWaveFolder
{
public:
    CMultiStageWaveFolder()
     : m_Stage()
     , m_NumStages(1)
    {
    }

    void SetNumStages(int NumStages)
    {
        m_NumStages = NumStages;
    }

    T operator()(T In, T Fold)
    {
        // assumes In is in [-1, 1] and Fold is in [0, 1]
        T Out = In;
        for(int idx = 0; idx<m_NumStages; ++idx)
        {
            Out = CSymmetricalOperator<T>()(Out, m_Stage, Fold);
            //Out = m_Stage(In, Fold);
        }
        return Out;
    }

private:
    CWaveFolderStage<T> m_Stage;
    int m_NumStages;
};

#endif // WAVEFOLDER2_H
