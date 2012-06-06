#ifndef _ILOADBALANCINGALGORITHM_H
#define _ILOADBALANCINGALGORITHM_H

#include <Core/ISolution.h>

#include "IModifiedSolutionBuilder.h"
#include "LoadBalancingProblem.h"
#include "IEnvironment.h"

class IModifiedSolutionBuilder;
class LoadBalancingProblem;
template<typename TProblem> class IEnvironment;

class ILoadBalancingAlgorithm
{
public:
	virtual void Init(std::shared_ptr<IEnvironment<LoadBalancingProblem>> environment) const = 0;
	virtual void Run(std::shared_ptr<ISolution> solution, std::shared_ptr<IEnvironment<LoadBalancingProblem>> environment, std::shared_ptr<IModifiedSolutionBuilder> modifiedSolutionBuilder) const = 0;
};

#endif // _ILOADBALANCINGALGORITHM_H