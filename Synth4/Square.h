#ifndef SQUARE_H
#define SQUARE_H

template<class T>
class CSquare
{
public:
    T operator()(const T& Phase) const
    {
        return Phase*Phase;
    }
};

#endif // SQUARE_H
