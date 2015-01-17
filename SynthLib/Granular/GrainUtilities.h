#ifndef GRAINUTILITIES_H
#define GRAINUTILITIES_H

namespace grainutilities
{

int UpdateCounter(int Counter, int Step, int MaxCounter)
{
    return (Counter+Step)%MaxCounter;//TODO in cpp
}

}

#endif // GRAINUTILITIES_H
