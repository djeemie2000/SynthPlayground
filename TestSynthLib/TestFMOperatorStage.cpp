#include "UnitTest++.h"
#include "FMOperatorStage.h"
#include "SelectableOperatorFactory.h"

namespace
{

TEST(Constructor)
{
    const int SamplingFrequency = 44100;
    CFMOperatorStage<float> Operator(SamplingFrequency, CSelectableOperatorFactory::Create());

    //TODO
}

}
