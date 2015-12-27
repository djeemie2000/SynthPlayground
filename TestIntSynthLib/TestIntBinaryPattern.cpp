#include <cstdint>
#include "UnitTest++.h"
#include "IntBinaryPattern.h"

namespace
{

using namespace isl;

TEST(Pattern16Bit)
{
    isl::CBinaryPattern<std::uint16_t> Pattern;

    CHECK_EQUAL(0, Pattern.Get());

    Pattern.Reset(0x1234);
    CHECK_EQUAL(0x1234, Pattern.Get());

    Pattern.Next();
    CHECK_EQUAL(0x1235, Pattern.Get());

    Pattern.Prev();
    CHECK_EQUAL(0x1234, Pattern.Get());

    Pattern.Invert();
    CHECK_EQUAL(0xEDCB, Pattern.Get());

    Pattern.Invert();
    CHECK_EQUAL(0x1234, Pattern.Get());

    Pattern.Reset(0x0123);

    Pattern.RotateNext();
    CHECK_EQUAL(0x0246, Pattern.Get());

    Pattern.RotatePrev();
    CHECK_EQUAL(0x0123, Pattern.Get());

    Pattern.Reset(0x0103);

    Pattern.RotatePrev();
    CHECK_EQUAL(0x8081, Pattern.Get());

    Pattern.RotateNext();
    CHECK_EQUAL(0x0103, Pattern.Get());

    Pattern.Reset(0x8081);

    Pattern.RotateNext();
    CHECK_EQUAL(0x0103, Pattern.Get());
}

TEST(GetBit16Bit)
{
    isl::CBinaryPattern<std::uint16_t> Pattern;

    Pattern.Reset(0x9F24);

    CHECK(!Pattern.GetBit(0));
    CHECK(!Pattern.GetBit(1));
    CHECK(Pattern.GetBit(2));
    CHECK(!Pattern.GetBit(3));

    CHECK(!Pattern.GetBit(4));
    CHECK(Pattern.GetBit(5));
    CHECK(!Pattern.GetBit(6));
    CHECK(!Pattern.GetBit(7));

    CHECK(Pattern.GetBit(8));
    CHECK(Pattern.GetBit(9));
    CHECK(Pattern.GetBit(10));
    CHECK(Pattern.GetBit(11));

    CHECK(Pattern.GetBit(12));
    CHECK(!Pattern.GetBit(13));
    CHECK(!Pattern.GetBit(14));
    CHECK(Pattern.GetBit(15));
}

TEST(Mirror8Bit)
{
    isl::CBinaryPattern<std::uint16_t> Pattern;

    Pattern.Reset(0x1001);
    Pattern.Mirror();
    CHECK_EQUAL(0x8008, Pattern.Get());

    Pattern.Reset(0x0F00);
    Pattern.Mirror();
    CHECK_EQUAL(0x00F0, Pattern.Get());

    Pattern.Reset(0x9012);

    Pattern.Mirror();
    CHECK_EQUAL(0x4809, Pattern.Get());
}

TEST(FixedBitCount)
{
    isl::CBinaryPattern<std::uint16_t> Pattern;

    Pattern.ResetFixedBitCount(0);
    CHECK_EQUAL(0x0000, Pattern.Get());

    Pattern.ResetFixedBitCount(1);
    CHECK_EQUAL(0x0001, Pattern.Get());

    Pattern.ResetFixedBitCount(7);
    CHECK_EQUAL(0x007F, Pattern.Get());

    Pattern.ResetFixedBitCount(9);
    CHECK_EQUAL(0x01FF, Pattern.Get());

}

}
