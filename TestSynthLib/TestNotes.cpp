#include "UnitTest++.h"
#include "Notes.h"

namespace
{

TEST(NotesList)
{
    auto Actual = CreateNoteList();

    CHECK_EQUAL(11u, Actual.size());
}

}
