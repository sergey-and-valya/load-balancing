#ifndef _ITESTSYSTEM_H
#define _ITESTSYSTEM_H

#include <Core/ISolution.h>
#include <memory>

#include "LoadBalancingProblem.h"
#include "IEnvironment.h"

class LoadBalancingProblem;
template<TProblem> class IEnvironment;

class ITestSystem
{
public:
	virtual std::shared_ptr<ISolution> Init(std::shared_ptr<IEnvironment<LoadBalancingProblem>> environment) const = 0;
	virtual void Run(ISolution& solution, IEnvironment<LoadBalancingProblem>& environment) const = 0;
};

#endif // _ITESTSYSTEM_H