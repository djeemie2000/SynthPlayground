#include <vector>
#include <thread>
#include "UnitTest++.h"
#include "ReadWriteBuffer.h"

namespace
{

TEST(CheckAtomicStuff)
{
    std::atomic<bool> tmp;
    CHECK(tmp.is_lock_free());
}

TEST(Constructor)
{
    const int BufferSize = 8;
    const int NumBuffers = 4;
    CReadWriteBuffer<float> Buffer(BufferSize, NumBuffers);

    CHECK_EQUAL(BufferSize, Buffer.GetBufferCapacity());

    std::vector<float> DstBuffer(BufferSize);
    CHECK(!Buffer.Read(DstBuffer));
}

TEST(NonThreadedWriteOnceReadOnce)
{
    const int BufferSize = 8;
    const int NumBuffers = 4;
    CReadWriteBuffer<float> Buffer(BufferSize, NumBuffers);

    std::vector<float> SrcBuffer(BufferSize, 1.23f);
    CHECK(Buffer.Write(SrcBuffer.data(), SrcBuffer.size()));

    std::vector<float> DstBuffer(BufferSize + 2, 0.0f);
    CHECK(Buffer.Read(DstBuffer));
    CHECK_EQUAL(BufferSize, DstBuffer.size());
    CHECK_CLOSE(1.23f, DstBuffer.at(0), 0.001f);

    CHECK(!Buffer.Read(DstBuffer));
}

TEST(NonThreadedWriteMultipleReadMultiple)
{
    const int BufferSize = 8;
    const int NumBuffers = 4;
    CReadWriteBuffer<float> Buffer(BufferSize, NumBuffers);

    const int NumWrites = 3;
    for(int Repeat = 0; Repeat<NumWrites; ++Repeat)
    {
        std::vector<float> SrcBuffer(BufferSize, 1.23f+Repeat);
        CHECK(Buffer.Write(SrcBuffer.data(), SrcBuffer.size()));
    }

    for(int Repeat = 0; Repeat<NumWrites; ++Repeat)
    {
        std::vector<float> DstBuffer(BufferSize + 2, 0.0f);
        CHECK(Buffer.Read(DstBuffer));
        CHECK_EQUAL(BufferSize, DstBuffer.size());
        CHECK_CLOSE(1.23f+Repeat, DstBuffer.at(0), 0.001f);
    }

    std::vector<float> DstBuffer(BufferSize + 2, 0.0f);
    CHECK(!Buffer.Read(DstBuffer));
}

TEST(NonThreadedWriteTooManyTimesNoRead)
{
    const int BufferSize = 8;
    const int NumBuffers = 4;
    CReadWriteBuffer<float> Buffer(BufferSize, NumBuffers);

    for(int Repeat = 0; Repeat<NumBuffers; ++Repeat)
    {
        std::vector<float> SrcBuffer(BufferSize, 1.23f);
        CHECK(Buffer.Write(SrcBuffer.data(), SrcBuffer.size()));
    }
    for(int Repeat = 0; Repeat<NumBuffers*2; ++Repeat)
    {
        std::vector<float> SrcBuffer(BufferSize, 1.23f);
        CHECK(!Buffer.Write(SrcBuffer.data(), SrcBuffer.size()));
    }
}


}
