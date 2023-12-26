#include "TJobStream.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

int TJobStreamStatus::AverageCycles() const
{
    return static_cast<int>(round(static_cast<double>(Cycles - IdleCycles) / Completed));
}

double TJobStreamStatus::RejectionPercentage() const
{
    return static_cast<double>(Rejected) / Total;
}

double TJobStreamStatus::IdlePercentage() const
{
    return static_cast<double>(IdleCycles) / Cycles;
}

TJobStream::TJobStream(int total, double intensity, double performance)
    : Tasks(total)
    , Intensity(static_cast<int>(intensity * 100))
    , Performance(static_cast<int>(performance * 100))
    , Current(IdleTask)
    , LastTaskId(0)
    , Status({})
{
    srand(time(nullptr));
}

int TJobStream::Random()
{
    return rand() % 100;
}

void TJobStream::CreateTasks()
{
    if (Random() > Intensity)
    {
        return;
    }

    Status.Total++;

    if (Tasks.IsFull())
    {
        Status.Rejected++;
        return;
    }

    Tasks.Put(++LastTaskId);
}

void TJobStream::RunCycle()
{
    Status.Cycles++;

    if (Current == IdleTask)
    {
        if (Tasks.IsEmpty())
        {
            Status.IdleCycles++;
            return;
        }

        Current = Tasks.Poll();
    }

    if (Random() > Performance)
    {
        return;
    }

    Status.Completed++;
    Current = IdleTask;
}

const TJobStreamStatus& TJobStream::GetStatus() const
{
    return Status;
}