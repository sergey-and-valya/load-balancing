#ifndef _IWORKERMESSAGE_H
#define _IWORKERMESSAGE_H

#include "IEnvironment.h"
#include "IWorker.h"

template<typename TProblem>
class IEnvironment;

template<typename TProblem>
class IWorker;

template<typename TProblem>
class IWorkerMessage
{
public:
	virtual IWorker<TProblem>* CreateWorker(IEnvironment<TProblem>& environment) const = 0;
};

#endif // _IWORKERMESSAGE_H