#include "TProc.h"

#include <cstdlib>

double TProcStatus::IdlePercentage() const
{
    return static_cast<double>(IdleCycles) / Cycles;
}

TProc::TProc(double performance)
    : Performance(static_cast<int>(performance * 100))
    , Status({})
{}

bool TProc::RunCycle(int taskId)
{
    Status.Cycles++;

    if (taskId == IdleTask)
    {
        Status.IdleCycles++;
        return false;
    }

    if ((rand() % 100) > Performance)
    {
        return false;
    }

    return true;
}

const TProcStatus& TProc::GetStatus() const
{
    return Status;
}