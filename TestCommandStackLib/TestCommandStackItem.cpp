#include "UnitTest++.h"
#include "CommandStack.h"

namespace
{

TEST(DefaultConstructor)
{
    SCmdStackItem Item;

    CHECK_EQUAL(false, Item.BoolValue());
    CHECK_EQUAL(-1, Item.IntValue());
    CHECK_CLOSE(-1.0f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL(0u, Item.TimeStamp());
    CHECK_EQUAL("", Item.TextValue());
}

TEST(Setters)
{
    SCmdStackItem Item = SCmdStackItem().TextValue("Text").BoolValue(true).FloatValue(123.45f).IntValue(123).TimeStamp(56789);

    CHECK_EQUAL(true, Item.BoolValue());
    CHECK_EQUAL(123, Item.IntValue());
    CHECK_CLOSE(123.45f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL(56789u, Item.TimeStamp());
    CHECK_EQUAL("Text", Item.TextValue());
}


}
