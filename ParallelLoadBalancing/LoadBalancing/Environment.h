#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H

#include "IEnvironment.h"

class Environment : public IEnvironment
{
public:
	Environment(bool needLoadBalancing)
		: needLoadBalancing(needLoadBalancing)
	{
	}

	void Run(IMPICommunicator& comm, ITestingSystem& ts, ILoadBalancingAlgorithm& lb, IRebalancer& rb);

private:
	bool needLoadBalancing;
};

#endif