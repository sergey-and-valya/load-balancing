#ifndef _IENVIRONMENT_H
#define _IENVIRONMENT_H

#include <memory>

#include "ICommunicator.h"


template<typename TProblem>
class IEnvironment
{
public:
	virtual std::shared_ptr<ICommunicator> World() = 0;
	virtual std::shared_ptr<TProblem> Problem() const = 0;
};

#endif // _IENVIRONMENT_H