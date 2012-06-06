#include "ITestingSystem.h"
#include "ILoadBalancingAlgorithm.h"
#include "IEnvironment.h"
#include "IMPICommunicator.h"

#include "TestingSystem.h"
#include "LoadBalancingAlgorithm.h"
#include "Environment.h"
#include "Rebalancer.h"
#include "MPIWorldCommunicator.h"

#include <mpi.h>
#include "tests\Tests.h"

#define NEEDS_LOAD_BALANCING true

int main()
{
	RebalancerMoveLeftTest();
	RebalancerNoMoveTest();
	LoadBalancingTest();
	
	LoadBalancingCentralTest();

	MPI_Init(NULL, NULL);
	
	auto lb = LoadBalancingAlgorithm(6);
	auto rb = Rebalancer();
	auto ts = TestingSystem("C:\\StartMatrix\\matrix");
	auto comm = MPIWorldCommunicator();
	auto env = Environment(NEEDS_LOAD_BALANCING);

	env.Run(comm, ts, lb, rb);

	MPI_Finalize();
}