#include <vector>
#include <thread>
#include "UnitTest++.h"
#include "simplereadwritebuffer.h"

namespace
{

TEST(CheckAtomicStuff)
{
    std::atomic<int> tmp;
    CHECK(tmp.is_lock_free());
}

TEST(Constructor)
{
    const int Capacity = 8;
    CSimpleReadWriteBuffer<float> Buffer(Capacity);

    std::vector<float> DstBuffer(Capacity);
    CHECK_EQUAL(0, Buffer.Read(DstBuffer.data(), Capacity));
}

TEST(NonThreadedMaximalWriteOnceReadOnce)
{
    const int Capacity = 8;
    CSimpleReadWriteBuffer<float> Buffer(Capacity);

    std::vector<float> SrcBuffer(Capacity, 1.23f);
    CHECK_EQUAL(Capacity, Buffer.Write(SrcBuffer.data(), Capacity));

    std::vector<float> DstBuffer(Capacity + 2, 0.0f);
    CHECK_EQUAL(Capacity, Buffer.Read(DstBuffer.data(), DstBuffer.size()));
    CHECK_ARRAY_CLOSE(SrcBuffer.data(), DstBuffer.data(), Capacity, 0.0001f);

    CHECK_EQUAL(0, Buffer.Read(DstBuffer.data(), DstBuffer.size()));
    CHECK_EQUAL(0, Buffer.Read(DstBuffer.data(), DstBuffer.size()));
}

TEST(NonThreadedWriteReadOneManyTimes)
{
    const int Capacity = 8;
    CSimpleReadWriteBuffer<float> Buffer(Capacity);

    for(int Repeat = 1; Repeat<4*Capacity; ++Repeat)
    {
        float ExpectedValue = Repeat;
        CHECK_EQUAL(1, Buffer.Write(&ExpectedValue, 1));

        float ActualValue = 0.0f;
        CHECK_EQUAL(1, Buffer.Read(&ActualValue, 1));
        CHECK_CLOSE(ExpectedValue, ActualValue, 0.0001f);

        float Dummy = 0;
        CHECK_EQUAL(0, Buffer.Read(&Dummy, 1));
    }
}

TEST(NonThreadedWriteReadMultipleManyTimes)
{
    const int Capacity = 8;
    CSimpleReadWriteBuffer<float> Buffer(Capacity);

    for(int Repeat = 1; Repeat<4*Capacity; ++Repeat)
    {
        float ExpectedValue = Repeat;
        const int BufferSize = 3;
        std::vector<float> Src(BufferSize, ExpectedValue);
        CHECK_EQUAL(BufferSize, Buffer.Write(Src.data(), Src.size()));
        std::vector<float> Dst(BufferSize, 0.0f);
        CHECK_EQUAL(BufferSize, Buffer.Read(Dst.data(), Dst.size()));
        CHECK_ARRAY_CLOSE(Src.data(), Dst.data(), BufferSize, 0.0001f);
    }
}

TEST(NonThreadedWriteNoRead)
{
    const int Capacity = 8;
    CSimpleReadWriteBuffer<float> Buffer(Capacity);

    std::vector<float> Src(5, 0.0f);
    CHECK_EQUAL(2, Buffer.Write(Src.data(), 2));
    CHECK_EQUAL(3, Buffer.Write(Src.data(), 3));
    CHECK_EQUAL(3, Buffer.Write(Src.data(), 5));
    CHECK_EQUAL(0, Buffer.Write(Src.data(), 2));
}

TEST(NonThreadedWriteReadSome)
{
    const int Capacity = 8;
    CSimpleReadWriteBuffer<float> Buffer(Capacity);

    std::vector<float> Src(5, 0.0f);
    std::vector<float> Dst(5, 0.0f);
    CHECK_EQUAL(2, Buffer.Write(Src.data(), 2));
    CHECK_EQUAL(3, Buffer.Write(Src.data(), 3));
    CHECK_EQUAL(4, Buffer.Read(Dst.data(), 4));
    CHECK_EQUAL(5, Buffer.Write(Src.data(), 5));
    CHECK_EQUAL(1, Buffer.Write(Src.data(), 1));
//    CHECK_EQUAL(0, Buffer.Write(Src.data(), 5));
//    CHECK_EQUAL(0, Buffer.Write(Src.data(), 2));
    CHECK_EQUAL(1, Buffer.Read(Dst.data(), 1));
    CHECK_EQUAL(2, Buffer.Read(Dst.data(), 2));
    CHECK_EQUAL(4, Buffer.Write(Src.data(), 5));

    CHECK_EQUAL(0, Buffer.Write(Src.data(), 5));
    CHECK_EQUAL(2, Buffer.Read(Dst.data(), 2));
    CHECK_EQUAL(2, Buffer.Write(Src.data(), 5));
    CHECK_EQUAL(5, Buffer.Read(Dst.data(), 5));
    CHECK_EQUAL(3, Buffer.Read(Dst.data(), 5));

    CHECK_EQUAL(5, Buffer.Write(Src.data(), 5));
    CHECK_EQUAL(3, Buffer.Write(Src.data(), 5));

}


TEST(NonThreadedWriteAboveCapacity)
{
    const int Capacity = 8;
    CSimpleReadWriteBuffer<float> Buffer(Capacity);

    std::vector<float> Src(Capacity+1, 0.0f);
    CHECK_EQUAL(Capacity, Buffer.Write(Src.data(), Src.size()));
    CHECK_EQUAL(0, Buffer.Write(Src.data(), 2));//!!!!
}

TEST(NonThreadedWriteReadInParts)
{
    const int Capacity = 8;
    CSimpleReadWriteBuffer<float> Buffer(Capacity);

    std::vector<float> Src;
    while(Src.size()<Capacity)
    {
        Src.push_back(Src.size()+1);
    }
    CHECK_EQUAL(Capacity, Buffer.Write(Src.data(), Capacity));

    std::vector<float> Dst(Capacity+5, 0.0f);
    CHECK_EQUAL(3, Buffer.Read(Dst.data(), 3));
    CHECK_EQUAL(2, Buffer.Read(Dst.data()+3, 2));
    CHECK_EQUAL(3, Buffer.Read(Dst.data()+5, 5));
    CHECK_EQUAL(0, Buffer.Read(Dst.data()+Capacity, 2));
    CHECK_ARRAY_CLOSE(Src.data(), Dst.data(), Capacity, 0.0001f);
}


//TEST(NonThreadedWriteMultipleReadMultiple)
//{
//    const int Capacity = 8;
//    CSimpleReadWriteBuffer<float> Buffer(Capacity);

//    const int NumWrites = 3;
//    for(int Repeat = 0; Repeat<NumWrites; ++Repeat)
//    {
//        std::vector<float> SrcBuffer(3, 1.23f+Repeat);
//        CHECK_EQUAL(3, Buffer.Write(SrcBuffer.data(), SrcBuffer.size()));
//    }

//    for(int Repeat = 0; Repeat<NumWrites; ++Repeat)
//    {
//        std::vector<float> DstBuffer(Capacity + 2, 0.0f);
//        CHECK_EQUAL(0, Buffer.Read(DstBuffer.data(), DstBuffer.size()));
//        CHECK_EQUAL(Capacity, DstBuffer.size());
//        CHECK_CLOSE(1.23f+Repeat, DstBuffer.at(0), 0.001f);
//    }

//    std::vector<float> DstBuffer(Capacity + 2, 0.0f);
//    CHECK_EQUAL(0, Buffer.Read(DstBuffer.data(), DstBuffer.size()));
//}

//TEST(NonThreadedWriteTooManyTimesNoRead)
//{
//    const int Capacity = 8;
//    CSimpleReadWriteBuffer<float> Buffer(Capacity);

//    for(int Repeat = 0; Repeat<4; ++Repeat)
//    {
//        std::vector<float> SrcBuffer(Capacity, 1.23f);
//        CHECK(Buffer.Write(SrcBuffer.data(), SrcBuffer.size()));
//    }
//    for(int Repeat = 0; Repeat<4*2; ++Repeat)
//    {
//        std::vector<float> SrcBuffer(Capacity, 1.23f);
//        CHECK(!Buffer.Write(SrcBuffer.data(), SrcBuffer.size()));
//    }
//}


}
