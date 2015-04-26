#pragma once

template<class T>
class CScaler
{
public:
    CScaler()
    {}

    T operator()(T In, T Scale, T Offset)
    {
        return In*Scale + Offset;
    }
};
