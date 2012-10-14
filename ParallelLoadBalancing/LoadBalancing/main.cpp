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

#include <LoadBalancing/IDomainModel.h>
#include <LoadBalancing/ILoadBalancingAlgorithm.h>
#include <LoadBalancing/IEnvironment.h>
#include <LoadBalancing/IMPICommunicator.h>

#include "SampleFunction.h"
#include "DomainModel.h"
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

#include <string>

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
	int steps;
	int world_size;
	ILoadBalancingAlgorithm* lba;
	IRebalancer* rb;
	IEnvironment* env;

	
	
	Config() : config_file()
		     , runTests(false)
			 , steps(10)
			 , world_size(4)
			 , matrix_file("matrix_big")
			 , lba(0)
			 , rb(0)
			 , env(0)
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

ILoadBalancingAlgorithm* lua_checkAlgorithm(lua_State* L)
{
	lua_getfield(L, -1, "AsILoadBalancingAlgorithm");
	lua_pushvalue(L, -2);
	lua_pcall(L, 1, 1, 0);
	return (ILoadBalancingAlgorithm*)lua_touserdata(L, -1);
}

IRebalancer* lua_checkRebalancer(lua_State* L)
{
	lua_getfield(L, -1, "AsIRebalancer");
	lua_pushvalue(L, -2);
	lua_pcall(L, 1, 1, 0);
	return (IRebalancer*)lua_touserdata(L, -1);
}

IEnvironment* lua_checkEnvironment(lua_State* L)
{
	lua_getfield(L, -1, "AsIEnvironment");
	lua_pushvalue(L, -2);
	lua_pcall(L, 1, 1, 0);
	return (IEnvironment*)lua_touserdata(L, -1);
}

void LoadConfig(lua_State* L, Config* cfg)
{
	if(luaL_loadfile(L, cfg->config_file.c_str()))
	{
		printf("problem during loading config file '%s':\n%s\n", cfg->config_file.c_str(), lua_tostring(L, -1));
		exit(1);
	}
	
	if(lua_pcall(L, 0, 0, 0))
	{
		printf("problem during executing config file '%s':\n%s\n", cfg->config_file.c_str(), lua_tostring(L, -1));
		exit(1);
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

	lua_getglobal(L, "matrix_file");
	if(!lua_isnil(L, -1))
	{
		cfg->matrix_file = lua_tostring(L, -1);
	}

	lua_getglobal(L, "unit_tests");
	if(!lua_isnil(L, -1))
	{
		cfg->runTests = lua_toboolean(L, -1);
	}

	lua_getglobal(L, "load_balancing_algorithm");
	if(!lua_isnil(L, -1))
	{
		cfg->lba = lua_checkAlgorithm(L);
	}

	lua_getglobal(L, "rebalancer");
	if(!lua_isnil(L, -1))
	{
		cfg->rb = lua_checkRebalancer(L);
	}

	lua_getglobal(L, "environment");
	if(!lua_isnil(L, -1))
	{
		cfg->env = lua_checkEnvironment(L);
	}
}

void Run(IMPICommunicator& comm, const Config& cfg)
{
	auto f = BinaryFile(cfg.matrix_file.c_str());
	auto func = SampleFunction();
	auto ts = DomainModel(f, func, cfg.steps);
	
	cfg.env->Run(comm, ts, *cfg.lba, *cfg.rb);
}

int main(int argc, char* argv[])
{
	Config cfg;
	
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	lua_getglobal(L, "package");
	lua_getfield(L, -1, "cpath");
	std::string cpath = std::string(argv[0]).append(";").append(lua_tostring(L, -1));
	lua_pop(L, 1);
	lua_pushstring(L, cpath.c_str());
	lua_setfield(L, -2, "cpath");
	lua_pop(L, 1);
	
	ParseCommandLine(argc, argv, &cfg);

	if(!cfg.config_file.empty())
	{
		LoadConfig(L, &cfg);
	}

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
    {
#ifdef EMULATE_MPI
	    clock_t start_time = clock();
	    TestMPIWorld world(cfg.world_size, [&cfg](IMPICommunicator& comm)
	    {
			Run(comm, cfg);
	    });

	    world.RunAndWait();
	
	    //printf("with%s load balancing %f\n", cfg.useLoadBalancing ? "" : "out", (float)(clock() - start_time) / CLOCKS_PER_SEC);
#else
	    MPI_Init(NULL, NULL);
	
	    auto comm = MPIWorldCommunicator();
		
		Run(comm, cfg);

	    MPI_Finalize();
#endif
    }
	
	lua_close(L);

	return 0;
}
