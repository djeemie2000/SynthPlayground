#include "UnitTest++.h"
#include "IntOperatorFactory.h"

namespace
{

using namespace isl;

TEST(Names)
{
    auto Names = COperatorFactory<8>::AvailableOperatorNames();
    CHECK_EQUAL(8, Names.size());
}

TEST(Operators)
{
    IntOperator Op = COperatorFactory<8>::GetOperator(0);
    CHECK_EQUAL(0, Op(0));
}

}
