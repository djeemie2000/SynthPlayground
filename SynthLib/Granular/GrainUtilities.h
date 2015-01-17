#ifndef GRAINUTILITIES_H
#define GRAINUTILITIES_H

namespace grainutilities
{

template<class T>
int UpdateCounter(T Counter, T Step, T MaxCounter)
{
    return (Counter+Step)%MaxCounter;//TODO in cpp
}

}

#endif // GRAINUTILITIES_H
