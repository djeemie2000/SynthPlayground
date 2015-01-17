#ifndef GRAINWINDOW_H
#define GRAINWINDOW_H

template<class T>
class CTriangularGrainWindow//TODO rename to CTriangularGrainWindow
{
public:
    CTriangularGrainWindow(){}

    T operator()(int Index, int GrainSize)
    {
        // an integer implementation of Triangle which can be rescaled to T in [0,1]
        return static_cast<T>( 2*Index<GrainSize ? 2*Index : 2*(GrainSize-Index))/static_cast<T>(GrainSize);
        // TODO return m_Op(Phase)
        // Phase should be in [0,1]
        // window should be in [0,1]
        // -> e.g. PseudoSin, Triangle,
        T Phase = static_cast<T>(Index)/static_cast<T>(GrainSize);
        return 4*Phase*(1-Phase);
    }
};

//TODO windows with short attack/decrease and sustain at 1

#endif // GRAINWINDOW_H
