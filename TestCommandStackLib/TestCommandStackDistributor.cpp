#include "UnitTest++.h"
#include "CommandStackDistributor.h"

namespace
{

TEST(Constructor)
{
    CCommandStackDistributor Distributor;

    Distributor.Register("Name", SPCommandStackHandler());
}

}
