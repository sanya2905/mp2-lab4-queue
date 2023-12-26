#include <gtest.h>
#include "TProc.h"

TEST(TProc, can_create_proc)
{
    EXPECT_NO_THROW(TProc(0.5));
}

TEST(TProc, proc_with_zero_performance_is_not_performant)
{
    TProc proc(0);

    for (int i = 0; i < 100; i++)
    {
        EXPECT_EQ(false, proc.RunCycle(i));
    }
}

TEST(TProc, proc_with_max_performance_is_performant)
{
    TProc proc(1);

    for (int i = 0; i < 100; i++)
    {
        EXPECT_EQ(true, proc.RunCycle(i));
    }
}

TEST(TProc, proc_with_idle_tasks_is_idle)
{
    TProc proc(1);

    const int cycles = 100;
    for (int i = 0; i < cycles; i++)
    {
        proc.RunCycle(TProc::IdleTask);
    }

    EXPECT_EQ(cycles, proc.GetStatus().IdleCycles);
    EXPECT_EQ(cycles, proc.GetStatus().Cycles);
}