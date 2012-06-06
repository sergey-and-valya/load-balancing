#ifndef _ICOMMUNICATOR_H
#define _ICOMMUNICATOR_H

#include <memory>
#include <vector>

class ICommunicator
{
public:
	virtual int Rank() = 0;
	virtual int Size() = 0;
	
	virtual std::shared_ptr<ICommunicator> Split(std::vector<int> processors) const = 0;
	virtual void Barrier() const = 0;
	virtual void Send(void* data, int sizeOfData) const = 0;
	virtual void Receive(void* data, int sizeOfData) const = 0;
};

#endif // _ICOMMUNICATOR_H