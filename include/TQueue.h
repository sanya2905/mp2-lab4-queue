#ifndef __TQUEUE__
#define __TQUEUE__

#include <stdexcept>

template<typename T>
class TQueue
{
private:
    T* pMem;
    int MemSize;
    int DataCount;
    int Hi, Li;

public:
    TQueue(int size = 8)
        : MemSize(size)
        , DataCount(0)
        , Hi(0)
        , Li(MemSize - 1)
        , pMem(new T[size])
    {}

    TQueue(const TQueue& other)
        : pMem(new T[other.MemSize])
        , MemSize(other.MemSize)
        , DataCount(other.DataCount)
        , Hi(other.Hi)
        , Li(other.Li)
    {}

    ~TQueue()
    {
        delete[] pMem;
    }
    
    TQueue& operator=(const TQueue& other)
    {
        if (this != &other)
        {
            TQueue tmp(other);
            swap(pMem, tmp.pMem);
            swap(MemSize, tmp.MemSize);
            swap(DataCount, tmp.DataCount);
            swap(Hi, tmp.Hi);
            swap(Li, tmp.Li);
        }
        return *this;
    }

    void Put(T element)
    {
        if (DataCount == MemSize)
        {
            throw std::logic_error("Queue is full");
        }

        Li = (Li + 1) % MemSize;
        pMem[Li] = element;
        DataCount++;
    }

    T Poll()
    {
        if (DataCount == 0)
        {
            throw std::logic_error("Queue is empty");
        }

        T element = pMem[Hi];
        Hi = (Hi + 1) % MemSize;
        DataCount--;

        return element;
    }

    bool IsEmpty() const
    {
        return DataCount == 0;
    }

    bool IsFull() const
    {
        return DataCount == MemSize;
    }

    bool Size() const
    {
        return DataCount;
    }

};

#endif // __TQUEUE__