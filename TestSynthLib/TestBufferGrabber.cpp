#include "UnitTest++.h"
#include "BufferGrabber.h"

namespace
{

TEST(Constructor)
{
    const int Capacity = 32;
    CBufferGrabber<float> Grabber(Capacity);

    CHECK_EQUAL(Capacity, Grabber.GetSize());
    for(int idx = 0; idx<Capacity; ++ idx)
    {
        CHECK_CLOSE(0.0f, Grabber.GetBuffer()[idx], 0.0001f);
    }
}

TEST(SetSize)
{
    const int Capacity = 32;
    CBufferGrabber<float> Grabber(Capacity);

    Grabber.SetSize(14);
    CHECK_EQUAL(14, Grabber.GetSize());

    Grabber.SetSize(-1);
    CHECK_EQUAL(14, Grabber.GetSize());

    Grabber.SetSize(Capacity+10);
    CHECK_EQUAL(14, Grabber.GetSize());

    Grabber.SetSize(2);
    CHECK_EQUAL(2, Grabber.GetSize());
}

TEST(NotGrabbing)
{
    const int Capacity = 32;
    CBufferGrabber<float> Grabber(Capacity);


    for(int idx = 0; idx<Capacity; ++ idx)
    {
        Grabber(1.0f);
    }

    for(int idx = 0; idx<Capacity; ++ idx)
    {
        CHECK_CLOSE(0.0f, Grabber.GetBuffer()[idx], 0.0001f);
    }

}

TEST(Grabbing)
{
    const int Capacity = 32;
    CBufferGrabber<float> Grabber(Capacity);


    Grabber.Grab();
    for(int idx = 0; idx<Capacity; ++ idx)
    {
        Grabber(1.0f);
    }
    for(int idx = 0; idx<Capacity; ++ idx)
    {
        CHECK_CLOSE(1.0f, Grabber.GetBuffer()[idx], 0.0001f);
    }

    // Grab only triggers one full buffer grab
    for(int idx = 0; idx<Capacity/2; ++ idx)
    {
        Grabber(2.0f);
    }
    for(int idx = 0; idx<Capacity; ++ idx)
    {
        CHECK_CLOSE(1.0f, Grabber.GetBuffer()[idx], 0.0001f);
    }
}

TEST(SetSizeGrabbing)
{
    const int Capacity = 32;
    CBufferGrabber<float> Grabber(Capacity);

    Grabber.SetSize(10);
    Grabber.Grab();
    for(int idx = 0; idx<Capacity; ++ idx)
    {
        Grabber(1.0f);
    }
    // Grab only triggers one full buffer size grab
    for(int idx = 0; idx<10; ++ idx)
    {
        CHECK_CLOSE(1.0f, Grabber.GetBuffer()[idx], 0.0001f);
    }
    for(int idx = 10; idx<Capacity; ++ idx)
    {
        CHECK_CLOSE(0.0f, Grabber.GetBuffer()[idx], 0.0001f);
    }
}

}
