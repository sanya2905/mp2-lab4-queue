#include "TJobStream.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "TProc.h"

double TJobStreamStatus::RejectionPercentage() const
{
    return static_cast<double>(Rejected) / Total;
}

TJobStream::TJobStream(int total, double intensity, TProc proc)
    : Tasks(total)
    , Intensity(static_cast<int>(intensity * 100))
    , Proc(proc)
    , Current(TProc::IdleTask)
    , LastTaskId(0)
    , Status({})
{
    srand(time(nullptr));
}

void TJobStream::CreateTasks()
{
    if ((rand() % 100) > Intensity)
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
    if (Current == TProc::IdleTask && !Tasks.IsEmpty())
    {
        Current = Tasks.Poll();
    }

    if (Proc.RunCycle(Current))
    {
        Status.Completed++;
    }

    Current = TProc::IdleTask;
}

int TJobStream::AverageCycles() const
{
    return static_cast<int>(round(static_cast<double>(
        Proc.GetStatus().Cycles - Proc.GetStatus().IdleCycles) / Status.Completed));
}

const TProc& TJobStream::GetProc() const
{
    return Proc;
}

const TJobStreamStatus& TJobStream::GetStatus() const
{
    return Status;
}