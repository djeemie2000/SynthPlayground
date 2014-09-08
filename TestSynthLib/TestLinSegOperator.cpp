#include "UnitTest++.h"
#include "LinSegOperator.h"

namespace
{

TEST(SomeValues)
{
    CLinSegOperator<float> Op;
    CHECK_CLOSE(0.75, Op(-0.25, 0.0, 1.0, 0.0, 0.0), 0.001);
    CHECK_CLOSE(0.25, Op(-0.75, 0.0, 1.0, 0.0, 0.0), 0.001);
    CHECK_CLOSE(0.75, Op(0.50, 0.0, 0.0, 1.0, 0.5), 0.001);
    CHECK_CLOSE(1.00, Op(0.0, 0.0, 0.0, 1.0, 0.5), 0.001);
}

}
