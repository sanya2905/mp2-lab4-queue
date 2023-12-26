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

	TQueue(const TQueue& other) = delete;
	TQueue& operator=(const TQueue& other) = delete;

	~TQueue()
	{
		delete[] pMem;
	}

	void Put(T element)
	{
		if (DataCount == MemSize)
		{
			throw std::logic_error("Stack is full");
		}

		Li = (Li + 1) % MemSize;
      	pMem[Li] = element;
      	DataCount++;
	}

	T Poll()
	{
		if (DataCount == 0)
		{
			throw std::logic_error("Stack is empty");
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