#ifndef _IWORKER_H
#define _IWORKER_H

#include "ICommunicator.h"
#include "IEnvironment.h"

class ICommunicator;
template<typename TProblem> class IEnvironment;

template<typename TProblem>
class IWorker
{
public:
	virtual void Collector(IEnvironment<TProblem>& environment, ICommunicator& channel) const = 0;
	virtual void Receiver(IEnvironment<TProblem>& environment, ICommunicator& channel) const = 0;
};

#endif // _IWORKER_H