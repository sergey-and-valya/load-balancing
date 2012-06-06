#ifndef _ITASKDISPATCHER_H
#define _ITASKDISPATCHER_H

#include <memory>

#include "IWorkerMessage.h"
#include "IWorkerStatus.h"
#include "IWorker.h"
#include "ICommunicator.h"

class IWorkerStatus;
class ICommunicator;
template<typename TProblem> class IWorkerMessage;
template<typename TProblem> class IWorker;

template<typename TProblem>
class ITaskDispatcher
{
public:
	virtual void Register(std::shared_ptr<IWorkerMessage<TProblem>> message) = 0;
	virtual std::shared_ptr<IWorkerStatus> Run(std::shared_ptr<IWorkerMessage<TProblem>> message, std::shared_ptr<IWorker<TProblem>> worker) = 0;
};

#endif // _ITASKDISPATCHER_H