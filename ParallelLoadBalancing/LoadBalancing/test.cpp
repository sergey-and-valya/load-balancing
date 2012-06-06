#include "ICommunicator.h"
#include "IEnvironment.h"
#include "ILoadBalancingAlgorithm.h"
#include "IModifiedSolutionBuilder.h"
#include "IWorker.h"
#include "IWorkerMessage.h"
#include "IWorkerStatus.h"
#include "ITestSystem.h"
#include "LoadBalancingProblem.h"

void test()
{
	IEnvironment<LoadBalancingProblem>* env;
	ICommunicator* c;//


	
	ITestSystem* s;
	ILoadBalancingAlgorithm* lb;
	
	s->Init(env);

	if(env->World()->Rank() == 0)
	{
		env->Problem()->Data()[Index2D(i,j)];
	}
	while(true)
	{
	}
}