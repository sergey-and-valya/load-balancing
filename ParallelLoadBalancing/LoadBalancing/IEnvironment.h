#ifndef _IENVIRONMENT_H
#define _IENVIRONMENT_H

#include "IMPICommunicator.h"
#include "ITestingSystem.h"
#include "ILoadBalancingAlgorithm.h"
#include "IRebalancer.h"

class IEnvironment
{
public:
	virtual void Run(IMPICommunicator& comm, ITestingSystem& ts, ILoadBalancingAlgorithm& lb, IRebalancer& rb) = 0;
};

#endif