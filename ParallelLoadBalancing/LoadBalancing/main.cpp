// ****************************************************************************
// LOAD BALANCING
// Copyright (C) 2012 Gerasimov, Smoryakova, Katerov, Afanasov, Kulakovich, Sobolev
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ****************************************************************************

#include "ITestingSystem.h"
#include "ILoadBalancingAlgorithm.h"
#include "IEnvironment.h"
#include "IMPICommunicator.h"

#include "TestingSystem.h"
#include "LoadBalancingAlgorithm.h"
#include "Environment.h"
#include "Rebalancer.h"
#include "BinaryFile.h"
#include "MPIWorldCommunicator.h"

#include "tests\Tests.h"
#include "tests\utils\Testkit.h"
#include "tests\utils\TestMPIWorld.h"

#include <time.h>

void Usage()
{
	printf(
		"loadbalancing [-t] [-lb] [-p] [-s <steps>] [-w <world-size>] [-a <accuracy>] [-f <matrix-file>]\n"
		"   -t               - run tests (default false)\n"
		"   -lb              - use load balancing (default false)\n"
		"   -p               - print results (default false)\n"
		"   -s <steps>       - number of steps for test system (default 10)\n"
		"   -w <world-size>  - number of emulated processors (default 4)\n"
		"   -a <accuracy>    - accuracy for load balancing (default 6)\n"
        "   -f <matrix-file> - used matrix file (default matrix_big)\n"
	);
}

int main(int argc, char* argv[])
{
	bool runTests         = false;
	bool useLoadBalancing = false;
	bool printResults     = false;
	int steps             = 10;
	int accuracy          = 6;
	int world_size        = 4;
	const char* file      = "matrix_big";

	for(int i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-t") == 0)
		{
			runTests = true;
		}
		else if(strcmp(argv[i], "-lb") == 0)
		{
			useLoadBalancing = true;
		}
		else if(strcmp(argv[i], "-p") == 0)
		{
			printResults = true;
		}
		else if(strcmp(argv[i], "-s") == 0)
		{
			steps = atoi(argv[++i]);
		}
		else if(strcmp(argv[i], "-a") == 0)
		{
			accuracy = atoi(argv[++i]);
		}
		else if(strcmp(argv[i], "-w") == 0)
		{
			world_size = atoi(argv[++i]);
		}
		else if(strcmp(argv[i], "-f") == 0)
		{
			file = argv[++i];
		}
		else
		{
			Usage();
			exit(1);
		}
	}

	if(runTests)
	{
		//TEST(EnvironmentTest);

		TEST(RebalancerMoveFromLeftTest);
		TEST(RebalancerMoveFromRightTest);
		TEST(RebalancerMoveFromTopTest);
		TEST(RebalancerMoveFromBottomTest);
	
		TEST(RebalancerMoveToLeftTest);
		TEST(RebalancerMoveToRightTest);
		TEST(RebalancerMoveToTopTest);
		TEST(RebalancerMoveToBottomTest);

		TEST(RebalancerNoMoveTest);
	
		TEST(RebalancerMoveFromLeftFromTopTest);
		
		TEST(TestingSystemStep);
		TEST(TestingSystemLoadTest);

		TEST(LoadBalancingTest);
		TEST(LoadBalancingCentralTest);
	}
	else
    {
#ifdef EMULATE_MPI
	    clock_t start_time = clock();
	    TestMPIWorld world(world_size, [useLoadBalancing, accuracy, steps, printResults, file](IMPICommunicator& comm)
	    {
		    auto lb = LoadBalancingAlgorithm(accuracy);
		    auto rb = Rebalancer();
		    auto f = BinaryFile(file);
		    auto ts = TestingSystem(f, steps);
		    auto env = Environment(useLoadBalancing, printResults);

		    env.Run(comm, ts, lb, rb);
	    });

	    world.RunAndWait();
	
	    printf("with%s load balancing %f\n", useLoadBalancing ? "" : "out", (float)(clock() - start_time) / CLOCKS_PER_SEC);
#else
	    MPI_Init(NULL, NULL);
	
	    auto lb = LoadBalancingAlgorithm(accuracy);
	    auto rb = Rebalancer();
	    auto f = BinaryFile(file);
	    auto ts = TestingSystem(f, steps);
	    auto comm = MPIWorldCommunicator();
	    auto env = Environment(useLoadBalancing, printResults);

	    env.Run(comm, ts, lb, rb);

	    MPI_Finalize();
#endif
    }
	return 0;
}
