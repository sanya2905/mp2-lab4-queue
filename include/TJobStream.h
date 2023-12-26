#ifndef __TJOBSTREAM__
#define __TJOBSTREAM__

#include "TQueue.h"

struct TJobStreamStatus
{
    int Total;
    int Completed;
    int Rejected;

    int Cycles;
    int IdleCycles;

    int AverageCycles() const;

    double RejectionPercentage() const;
    double IdlePercentage() const;
};

class TJobStream
{
private:
    static const int IdleTask = -1;

    const int Intensity;
    const int Performance;

    TQueue<int> Tasks;

    int Current;
    int LastTaskId;

    TJobStreamStatus Status;

    static int Random();

public:
    TJobStream(int total, double intensity, double performance);

    void CreateTasks();
    void RunCycle();

    const TJobStreamStatus& GetStatus() const;
};

#endif // __TJOBSTREAM__