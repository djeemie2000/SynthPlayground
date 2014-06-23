#include "UnitTest++.h"
#include "Notes.h"

namespace
{

TEST(NotesList)
{
    auto Actual = CNoteList::Create();

    CHECK_EQUAL(12u, Actual.size());
}

}
