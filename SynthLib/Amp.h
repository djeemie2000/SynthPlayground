#ifndef AMP_H
#define AMP_H

template<class T>
class CAmp
{
public:
    CAmp(){}

    T operator()(T In, T Amplitude)
    {
        return Amplitude*In;
    }
};

#endif // AMP_H
