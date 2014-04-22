#ifndef CROSSFADER_H
#define CROSSFADER_H

template<class T>
class CCrossFader
{
public:
    CCrossFader(){}

    T operator()(const T& Value1, const T& Value2, const T& Mix)
    {
        return (1-Mix)*Value1 + Mix*Value2;
    }

    template<class Operator1Type, class Operator2Type>
    T operator()(Operator1Type Op1, Operator2Type Op2, const T& Phase, const T& Mix)
    {
        return (1-Mix)*Op1(Phase) + Mix*Op2(Phase);
    }
};

#endif // CROSSFADER_H
