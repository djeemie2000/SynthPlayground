#include "UnitTest++.h"
#include "RampUp.h"

namespace
{

TEST(RampUpFloat)
{
    CRampUp<float> Operator;
    CHECK_CLOSE(0.0f, Operator(0.0f), 0.00001);
    CHECK_CLOSE(-0.5f, Operator(-0.5f), 0.00001);
    CHECK_CLOSE(0.5f, Operator(0.5f), 0.00001);
    CHECK_CLOSE(1.0f, Operator(1.0f), 0.00001);
}

}
