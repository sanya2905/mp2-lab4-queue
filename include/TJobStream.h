#ifndef __TJOBSTREAM__
#define __TJOBSTREAM__

#include "TQueue.h"
#include "TProc.h"

struct TJobStreamStatus
{
    int Total;
    int Completed;
    int Rejected;

    double RejectionPercentage() const;
};

class TJobStream
{
private:
    const int Intensity;

    TQueue<int> Tasks;
    TProc Proc;

    int Current;
    int LastTaskId;

    TJobStreamStatus Status;

public:
    TJobStream(int total, double intensity, TProc proc);

    void CreateTasks();
    void RunCycle();

    int AverageCycles() const;

    const TProc& GetProc() const;
    const TJobStreamStatus& GetStatus() const;
};

#endif // __TJOBSTREAM__