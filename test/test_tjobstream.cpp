#include <gtest.h>
#include "TJobStream.h"

TEST(TProc, can_create_jobstream)
{
    EXPECT_NO_THROW(TJobStream(10, 0.5, 0.5));
}