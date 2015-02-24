#include <cstdint>
#include "UnitTest++.h"
#include "wavetable2.h"

namespace
{

TEST(SetWaveTableUint8FloatWholeInterval)
{
    wt2::CWaveTablePlayer<std::uint8_t, float, float> Player;

    std::uint8_t Data[] = { 0, 16, 32, 48, 64, 80, 96, 112 };
    const int DataSize = 8;
    Player.SetWaveTable(Data, DataSize);


    CHECK_CLOSE(-1.0f, Player(-1.0f, 0, DataSize), 0.001f);
    CHECK_CLOSE(-0.875f, Player(-0.75f, 0, DataSize), 0.001f);
    CHECK_CLOSE(-0.750f, Player(-0.5f, 0, DataSize), 0.001f);
    CHECK_CLOSE(-0.625f, Player(-0.25f, 0, DataSize), 0.001f);
    CHECK_CLOSE(-0.5f, Player(0.0f, 0, DataSize), 0.001f);
    CHECK_CLOSE(-0.375f, Player(0.25f, 0, DataSize), 0.001f);
    CHECK_CLOSE(-0.25f, Player(0.5f, 0, DataSize), 0.001f);
    CHECK_CLOSE(-0.125f, Player(0.75f, 0, DataSize), 0.001f);
    CHECK_CLOSE(-1.0f, Player(1.0f, 0, DataSize), 0.001f);
}

TEST(SetWaveTableUint8Begin)
{
    wt2::CWaveTablePlayer<std::uint8_t, float, std::uint8_t> Player;

    std::uint8_t Data[] = { 128, 144, 160, 176 };
    const int DataSize = 4;
    Player.SetWaveTable(Data, DataSize);

    CHECK_EQUAL(128, Player(-1.0f, 0, DataSize));
    CHECK_EQUAL(144, Player(-1.0f, 1, DataSize));
    CHECK_EQUAL(160, Player(-1.0f, 2, DataSize));
    CHECK_EQUAL(176, Player(-1.0f, 3, DataSize));

    CHECK_EQUAL(160, Player(-1.0f, 2, DataSize));
    CHECK_EQUAL(176, Player(-0.5f, 2, DataSize));
    CHECK_EQUAL(128, Player(-0.0f, 2, DataSize));
    CHECK_EQUAL(144, Player(0.5f, 2, DataSize));
    CHECK_EQUAL(160, Player(1.0f, 2, DataSize));

}

TEST(WaveTableManager)
{
    std::uint8_t Data[] = { 0, 16, 32, 48,
                            64, 60, 76, 92,
                            112, 128, 144, 160,
                            176, 192, 208, 224 };
    const int DataSize = 16;
    const int SingleWavesize = 4;

    wt2::CWaveTableManager<std::uint8_t, float, float> Manager(Data, DataSize, SingleWavesize);
}

}
