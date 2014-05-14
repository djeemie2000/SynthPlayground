#include "UnitTest++.h"
#include "PeriodicTicker.h"

namespace
{

TEST(ConstructorNotActive)
{
    CPeriodicTicker Ticker;

    for(int idx=0; idx<50;++idx)
    {
        CHECK(!Ticker());
    }
}

TEST(Active)
{
    CPeriodicTicker Ticker;
    Ticker.SetPeriod(2);
    Ticker.Activate(true);

    for(int idx=0; idx<10;++idx)
    {
        CHECK(Ticker());
        CHECK(!Ticker());
    }
}


}
