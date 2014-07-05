#include <vector>
#include "UnitTest++.h"
#include "PeriodicSampleGrabber.h"

namespace
{

TEST(SetSizeAndPeriod)
{
    CPeriodicSampleGrabber<int> Grabber;

    Grabber.SetGrabPeriod(4);
    Grabber.SetGrabSize(3);

    CHECK_EQUAL(3u, Grabber.GetGrabbedSample().size());
}

TEST(GrabPeriodExceedsSampleSize)
{
    CPeriodicSampleGrabber<int> Grabber;

    Grabber.SetGrabSize(3);
    Grabber.SetGrabPeriod(10);

    std::vector<int> Input = { 1, 2, 3, 4, 5, 6, 7, 8 };
    Grabber.OnRead(Input.data(), Input.size());

    std::vector<int> Expected1 = {1,2,3};
    CHECK_ARRAY_EQUAL(Expected1.data(), Grabber.GetGrabbedSample().data(), Expected1.size());

    Grabber.OnRead(Input.data(), Input.size());

    std::vector<int> Expected2 = { 3, 4, 5};
    CHECK_ARRAY_EQUAL(Expected2.data(), Grabber.GetGrabbedSample().data(), Expected2.size());

    Grabber.OnRead(Input.data(), Input.size());

    std::vector<int> Expected3 = { 5, 6, 7};
    CHECK_ARRAY_EQUAL(Expected3.data(), Grabber.GetGrabbedSample().data(), Expected3.size());
}

}
