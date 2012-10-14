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

#include "IDomainModel.h"
#include "ILoadBalancingAlgorithm.h"
#include "IEnvironment.h"
#include "IMPICommunicator.h"

#include "SampleFunction.h"
#include "DomainModel.h"
#include "LoadBalancingAlgorithm.h"
#include "Environment.h"
#include "Rebalancer.h"
#include "BinaryFile.h"
#include "MPIWorldCommunicator.h"

#ifdef WIN32
#include "tests/Tests.h"
#include "tests/utils/Testkit.h"
#include "tests/utils/TestMPIWorld.h"
#endif

#include <time.h>
#include <lua.hpp>
#include <string>
#include <string.h>
#include <stdlib.h>

void Usage()
{
	printf(
		"loadbalancing [-c <config-file>]\n"
		"   -c               - use specific lua config file\n"
	);
}

struct Config
{
	std::string config_file;
	
	std::string matrix_file;
	bool runTests;
	bool useLoadBalancing;
	bool printResults;
	int steps;
	int accuracy;
	int world_size;

	
	
	Config() : config_file()
		     , runTests(false)
			 , useLoadBalancing(false)
			 , printResults(false)
			 , steps(10)
			 , accuracy(6)
			 , world_size(4)
			 , matrix_file("matrix_big")
	{
	}
};

void ParseCommandLine(int argc, char* argv[], Config* cfg)
{
	for(int i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-c") == 0)
		{
			cfg->config_file = argv[++i];
		}
		else
		{
			Usage();
			exit(1);
		}
	}
}

void LoadConfig(Config* cfg)
{	
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	
	if(luaL_loadfile(L, cfg->config_file.c_str()))
	{
		printf("config file '%s' is not found\n", cfg->config_file.c_str());
		exit(1);
	}
	
	if(lua_pcall(L, 0, 0, 0))
	{
		printf("problem executing config file '%s':\n%s\n", cfg->config_file.c_str(), lua_tostring(L, -1));
		exit(1);
	}

	lua_getglobal(L, "load_balancing");
	if(!lua_isnil(L, -1))
	{
		cfg->useLoadBalancing = lua_toboolean(L, -1);
	}

	lua_getglobal(L,  "steps");
	if(!lua_isnil(L, -1))
	{
		cfg->steps = lua_tointeger(L, -1);
	}
	
	lua_getglobal(L, "world_size");
	if(!lua_isnil(L, -1))
	{
		cfg->world_size = lua_tointeger(L, -1);
	}

	lua_getglobal(L, "accuracy");
	if(!lua_isnil(L, -1))
	{
		cfg->accuracy = lua_tointeger(L, -1);
	}

	lua_getglobal(L, "matrix_file");
	if(!lua_isnil(L, -1))
	{
		cfg->matrix_file = lua_tostring(L, -1);
	}

	lua_getglobal(L, "print_results");
	if(!lua_isnil(L, -1))
	{
		cfg->printResults = lua_toboolean(L, -1);
	}

	lua_getglobal(L, "unit_tests");
	if(!lua_isnil(L, -1))
	{
		cfg->runTests = lua_toboolean(L, -1);
	}

	lua_close(L);	
}

int main(int argc, char* argv[])
{
	Config cfg;

	ParseCommandLine(argc, argv, &cfg);

	if(!cfg.config_file.empty())
	{
		LoadConfig(&cfg);
	}

#ifdef WIN32
	if(cfg.runTests)
	{
		// TODO: Add enviroment test system
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
		
		TEST(DomainModelStep);
		TEST(DomainModelLoadTest);

		TEST(LoadBalancingTest);
		TEST(LoadBalancingCentralTest);
	}
	else
#endif
    {
#ifdef EMULATE_MPI
	    clock_t start_time = clock();
	    TestMPIWorld world(cfg.world_size, [&cfg](IMPICommunicator& comm)
	    {
		    auto lb = LoadBalancingAlgorithm(cfg.accuracy);
		    auto rb = Rebalancer();
		    auto f = BinaryFile(cfg.matrix_file.c_str());
			auto func = SampleFunction();
		    auto ts = DomainModel(f, func, cfg.steps);
		    auto env = Environment(cfg.useLoadBalancing, cfg.printResults);

		    env.Run(comm, ts, lb, rb);
	    });

	    world.RunAndWait();
	
	    printf("with%s load balancing %f\n", cfg.useLoadBalancing ? "" : "out", (float)(clock() - start_time) / CLOCKS_PER_SEC);
#else
	    MPI_Init(NULL, NULL);
	
	    LoadBalancingAlgorithm lb(cfg.accuracy);
	    Rebalancer rb;
	    SampleFunction func;
	    BinaryFile f(cfg.matrix_file.c_str());
	    DomainModel ts(f, func, cfg.steps);
	    MPIWorldCommunicator comm;
	    Environment env(cfg.useLoadBalancing, cfg.printResults);

	    env.Run(comm, ts, lb, rb);

	    MPI_Finalize();
#endif
    }
	return 0;
}
