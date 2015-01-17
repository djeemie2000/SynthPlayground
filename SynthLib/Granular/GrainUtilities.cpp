#include "GrainUtilities.h"

namespace grainutilities
{

int UpdateCounter(int Counter, int Step, int MaxCounter)
{
    return (Counter+Step)%MaxCounter;
}

}

