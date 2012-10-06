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
#include <lua.hpp>

void Usage()
{
	printf(
		"loadbalancing [-c <config-file>]\n"
		"   -c               - use specific lua config file (default: config.default.lua)\n"
	);
}

int main(int argc, char* argv[])
{
	const char* config_file = "config.default.lua";

	for(int i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-c") == 0)
		{
			config_file = argv[++i];
		}
		else
		{
			Usage();
			exit(1);
		}
	}

	bool runTests;
	bool useLoadBalancing;
	bool printResults;
	int steps;
	int accuracy;
	int world_size;
	std::string file;

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	
	if(luaL_loadfile(L, config_file))
	{
		printf("config file '%s' is not found\n", config_file);
		exit(1);
	}
	
	if(lua_pcall(L, 0, 0, 0))
	{
		printf("problem executing config file '%s':\n%s\n", config_file, lua_tostring(L, -1));
		exit(1);
	}


	lua_getglobal(L, "load_balancing");
	useLoadBalancing = lua_toboolean(L, -1);
	

	lua_getglobal(L,  "steps");
	steps = lua_tointeger(L, -1);
	
	lua_getglobal(L, "world_size");
	world_size = lua_tointeger(L, -1);

	lua_getglobal(L, "accuracy");
	accuracy = lua_tointeger(L, -1);

	lua_getglobal(L, "matrix_file");
	file = std::string(lua_tostring(L, -1));

	lua_getglobal(L, "print_results");
	printResults = lua_toboolean(L, -1);

	lua_getglobal(L, "unit_tests");
	runTests = lua_toboolean(L, -1);

	lua_close(L);

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
		    auto f = BinaryFile(file.c_str());
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
	    auto f = BinaryFile(file.c_str());
	    auto ts = TestingSystem(f, steps);
	    auto comm = MPIWorldCommunicator();
	    auto env = Environment(useLoadBalancing, printResults);

	    env.Run(comm, ts, lb, rb);

	    MPI_Finalize();
#endif
    }
	return 0;
}
