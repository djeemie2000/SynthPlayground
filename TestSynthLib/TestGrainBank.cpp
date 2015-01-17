#include "UnitTest++.h"
#include "GrainBank.h"

namespace
{

TEST(Constructor)
{
    const int NumGrains = 4;
    CGrainBank<float> GrainBank(NumGrains);
}

}
