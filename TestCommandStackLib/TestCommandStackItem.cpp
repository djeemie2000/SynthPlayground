#include "UnitTest++.h"
#include "CommandStackItem.h"

namespace
{

TEST(DefaultConstructor)
{
    SCmdStackItem Item;

    CHECK_EQUAL(false, Item.BoolValue());
    CHECK_EQUAL(-1, Item.IntValue());
    CHECK_CLOSE(-1.0f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL("", Item.TextValue());
}

TEST(Constructors)
{
    std::string ExpectedName;
    bool ExpectedBool = false;
    int ExpectedInt = -1;
    float ExpectedFloat = -1.0f;

    SCmdStackItem Item1(ExpectedName);
    CHECK_EQUAL(ExpectedName, Item1.Name());
    CHECK_EQUAL(ExpectedBool, Item1.BoolValue());
    CHECK_EQUAL(ExpectedInt, Item1.IntValue());
    CHECK_EQUAL(ExpectedFloat, Item1.FloatValue());

    SCmdStackItem Item2(ExpectedName);
    CHECK_EQUAL(ExpectedName, Item2.Name());
    CHECK_EQUAL(false, Item2.BoolValue());
    CHECK_EQUAL(-1, Item2.IntValue());
    CHECK_CLOSE(-1.0f, Item2.FloatValue(), 0.001f);
}

TEST(Setters)
{
    SCmdStackItem Item = SCmdStackItem().TextValue("Text").BoolValue(true).FloatValue(123.45f).IntValue(123);

    CHECK_EQUAL(true, Item.BoolValue());
    CHECK_EQUAL(123, Item.IntValue());
    CHECK_CLOSE(123.45f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL("Text", Item.TextValue());
}

TEST(BoolValueFromString)
{
    SCmdStackItem Item = SCmdStackItem("Name").BoolValue(false);
    SCmdStackItem Item2 = Item.ValueFromString("1");

    CHECK_EQUAL("Name", Item2.Name());
    CHECK_EQUAL(true, Item2.BoolValue());
    CHECK_EQUAL(-1, Item2.IntValue());
    CHECK_CLOSE(-1.0f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL("", Item.TextValue());
}

TEST(IntValueFromString)
{
    SCmdStackItem Item = SCmdStackItem("Name").IntValue(54321);
    SCmdStackItem Item2 = Item.ValueFromString("12345678");

    CHECK_EQUAL("Name", Item2.Name());
    CHECK_EQUAL(false, Item2.BoolValue());
    CHECK_EQUAL(12345678, Item2.IntValue());
    CHECK_CLOSE(-1.0f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL("", Item.TextValue());
}

TEST(FloatValueFromString)
{
    SCmdStackItem Item = SCmdStackItem("Name").FloatValue(1.234f);
    SCmdStackItem Item2 = Item.ValueFromString("98.765");

    CHECK_EQUAL("Name", Item2.Name());
    CHECK_EQUAL(false, Item2.BoolValue());
    CHECK_EQUAL(-1, Item2.IntValue());
    CHECK_CLOSE(98.765f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL("", Item.TextValue());
}

TEST(TextValueFromString)
{
    SCmdStackItem Item = SCmdStackItem("Name").TextValue("abc");
    SCmdStackItem Item2 = Item.ValueFromString("defghij");

    CHECK_EQUAL("Name", Item2.Name());
    CHECK_EQUAL(false, Item2.BoolValue());
    CHECK_EQUAL(-1, Item2.IntValue());
    CHECK_CLOSE(-1.0f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL("defghij", Item.TextValue());
}

TEST(TextValueFromFloatFailed)
{
    SCmdStackItem Item = SCmdStackItem("Name").FloatValue(1.23f);
    SCmdStackItem Item2 = Item.ValueFromString("defghij");

    CHECK_EQUAL("Name", Item2.Name());
    CHECK_EQUAL(false, Item2.BoolValue());
    CHECK_EQUAL(-1, Item2.IntValue());
    CHECK_CLOSE(1.23f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL("", Item.TextValue());
}

TEST(CreateFromStringBool)
{
    SCmdStackItem Item("MyName", "Boolean", "1");
    CHECK_EQUAL("MyName", Item.Name());
    CHECK_EQUAL(true, Item.BoolValue());
    CHECK_EQUAL(-1, Item.IntValue());
    CHECK_CLOSE(-1.0f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL("", Item.TextValue());
}

TEST(CreateFromStringInteger)
{
    SCmdStackItem Item("MyName", "Integer", "12345");
    CHECK_EQUAL("MyName", Item.Name());
    CHECK_EQUAL(false, Item.BoolValue());
    CHECK_EQUAL(12345, Item.IntValue());
    CHECK_CLOSE(-1.0f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL("", Item.TextValue());
}

TEST(CreateFromStringFloat)
{
    SCmdStackItem Item("Name", "Float", "-3.215");
    CHECK_EQUAL("Name", Item.Name());
    CHECK_EQUAL(false, Item.BoolValue());
    CHECK_EQUAL(-1, Item.IntValue());
    CHECK_CLOSE(-3.215f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL("", Item.TextValue());
}

TEST(CreateFromStringText)
{
    SCmdStackItem Item("Name", "Text", "-3.215");
    CHECK_EQUAL("Name", Item.Name());
    CHECK_EQUAL(false, Item.BoolValue());
    CHECK_EQUAL(-1, Item.IntValue());
    CHECK_CLOSE(-1.0f, Item.FloatValue(), 0.0001);
    CHECK_EQUAL("-3.215", Item.TextValue());
    CHECK_EQUAL("Text", Item.Type());
    CHECK_EQUAL("-3.215", Item.Value());
}

}
