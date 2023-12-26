#ifndef __TPROC__
#define __TPROC__

struct TProcStatus
{
    int Cycles;
    int IdleCycles;

    double IdlePercentage() const;
};

class TProc
{
public:
    static const int IdleTask = -1;
private:
    int Performance;
    TProcStatus Status;

public:
    TProc(double performance);

    bool RunCycle(int taskId);

    const TProcStatus& GetStatus() const;
};

#endif // __TPROC__