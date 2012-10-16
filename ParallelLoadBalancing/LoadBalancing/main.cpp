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
#include <LoadBalancing/LuaAPI/LuaAPI.h>
#include <LoadBalancing/LuaAPI/ILoadBalancingAlgorithm.h>
#include <LoadBalancing/LuaAPI/IRebalancer.h>
#include <LoadBalancing/LuaAPI/IEnvironment.h>

#include "StandartLuaModule.h"

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

void Usage(const char* path)
{
	const char sep =
#ifdef WIN32
		'\\';
#else
		'/';
#endif

	const char* filename = path;
	const char* p = path;
	while(*p)
	{
		if((*p) == sep)
		{
			filename = p + 1;
		}
		p++;
	};

	printf(
		"%s "
#ifdef EMULATE_MPI
		"Emulate "
#endif
		"MPI "
#ifdef WIN32
		"Windows"
#else
		"Linux"
#endif
		" version\n"
		"%s [-c <config-file>] "
#ifdef EMULATE_MPI
		"[-w <number>] "
#endif
#ifdef WIN32
		"[-t]\n"
#endif
		"   -c <config-file>  - use specific lua config file\n"
#ifdef EMULATE_MPI
		"   -w <number>       - world size, count of emulated mpi-processors\n"
#endif
#ifdef WIN32
		"   -t                - run unit tests instead of load balancing\n"
#endif
		, filename, filename
	);
}

struct Config
{
	std::string config_file;
	
#ifdef WIN32
	bool unit_tests;
#endif
	ILoadBalancingAlgorithm* lba;
	IRebalancer* rb;
	IEnvironment* env;
	IDomainModel* dm;

	
	
	Config() : config_file()
#ifdef WIN32
		     , unit_tests(false)
#endif
			 , lba(0)
			 , rb(0)
			 , env(0)
			 , dm(0)
	{
	}
};

void ParseCommandLine(int argc, char* argv[], Config* cfg, bool silent)
{
	bool config_file_isset = false;
#ifdef WIN32
	bool unit_tests_isset = false;
#endif

	for(int i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-c") == 0)
		{
			cfg->config_file = argv[++i];

			if(config_file_isset)
			{
				if(!silent)
				{
					printf("Config file option is already set");
				}
				exit(1);
			}
			config_file_isset = true;
		}
#ifdef WIN32
		else if(strcmp(argv[i], "-t") == 0)
		{
			cfg->unit_tests = true;

			if(unit_tests_isset)
			{
				if(!silent)
				{
					printf("Unit tests option is already set");
				}
				exit(1);
			}
			unit_tests_isset = true;
		}
#endif
#ifdef EMULATE_MPI
		else if(strcmp(argv[i], "-w") == 0)
		{
			i++;
		}
#endif
		else
		{
			if(!silent)
			{
				printf("Wrong parameter: %s\n", argv[i]);
				Usage(argv[0]);
			}
			exit(1);
		}
	}

#ifdef WIN32
	if(!(unit_tests_isset || config_file_isset))
	{
		printf("You must specify either config file or turn on unit tests option!");
		exit(1);
	}
#else
	if(!config_file_isset)
	{
		printf("You must specify config file option!");
		exit(1);
	}
#endif
}


#ifdef EMULATE_MPI
struct EmulateMPIConfig
{
	int world_size;
};

void ParseEmulateMPICommandLine(int argc, char* argv[], EmulateMPIConfig* cfg)
{
	bool world_size_isset = false;

	for(int i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-c") == 0)
		{
			i++;
		}
#ifdef WIN32
		else if(strcmp(argv[i], "-t") == 0)
		{
		}
#endif
		else if(strcmp(argv[i], "-w") == 0)
		{
			cfg->world_size = atoi(argv[++i]);

			if(world_size_isset)
			{
				printf("World size option is already set");
				exit(1);
			}
			world_size_isset = true;
		}
		else
		{
			printf("Wrong parameter: %s\n", argv[i]);
			Usage(argv[0]);
			exit(1);
		}
	}

	if(!world_size_isset)
	{
		printf("You must specify a world size!");
		exit(1);
	}
}
#endif

IDomainModel* lua_checkDomainModel(lua_State* L)
{
	lua_getfield(L, -1, "AsIDomainModel");
	lua_pushvalue(L, -2);
	lua_pcall(L, 1, 1, 0);
	return (IDomainModel*)lua_touserdata(L, -1);
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

	lua_getglobal(L, "load_balancing_algorithm");
	if(!lua_isnil(L, -1))
	{
		cfg->lba = *luaLB_checkILoadBalancingAlgorithm(L, -1);
	}

	lua_getglobal(L, "rebalancer");
	if(!lua_isnil(L, -1))
	{
		cfg->rb = *luaLB_checkIRebalancer(L, -1);
	}

	lua_getglobal(L, "environment");
	if(!lua_isnil(L, -1))
	{
		cfg->env = *luaLB_checkIEnvironment(L, -1);
	}

	lua_getglobal(L, "domain_model");
	if(!lua_isnil(L, -1))
	{
		cfg->dm = lua_checkDomainModel(L);
	}
}

int luaLB_clock(lua_State* L)
{
	lua_pushnumber(L, clock());

	return 1;
}

void Run(IMPICommunicator& comm, int argc, char* argv[])
{
	Config cfg;
	
	int rank;
	comm.Rank(&rank);
	
	ParseCommandLine(argc, argv, &cfg, rank == 0);

#if WIN32
	if(cfg.unit_tests)
	{
		if(rank == 0)
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
	}
	else
#endif
    {
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		luaLB_openlibs(L);
		lua_registerStandartModuleLoader(L);

		lua_pushcfunction(L, luaLB_clock);
		lua_setglobal(L, "time");

		LoadConfig(L, &cfg);

		if(rank == 0)
		{
			lua_getglobal(L, "on_start");
			if(!lua_isnil(L, -1))
			{
				if(lua_pcall(L, 0, 0, 0))
				{
					printf("problem during executing on_start function:\n%s\n", lua_tostring(L, -1));
					exit(1);
				}
			}
		}
		
		cfg.env->Run(comm, *cfg.dm, *cfg.lba, *cfg.rb);

		int fake_buff;
		MPI_Status status;
		if(rank == 0)
		{
			int size;
			comm.Size(&size);
			for(int i = 1; i < size; i++)
			{
				comm.Recv(&fake_buff, 1, MPI_INT, i, 0, &status);
			}
			
			lua_getglobal(L, "on_stop");
			if(!lua_isnil(L, -1))
			{
				if(lua_pcall(L, 0, 0, 0))
				{
					printf("problem during executing on_stop function:\n%s\n", lua_tostring(L, -1));
					exit(1);
				}
			}
		}
		else
		{
			comm.Send(&fake_buff, 1, MPI_INT, 0, 0);
		}
		
		lua_close(L);
	}
}

int main(int argc, char* argv[])
{
#ifdef EMULATE_MPI
	EmulateMPIConfig cfg;
	ParseEmulateMPICommandLine(argc, argv, &cfg);

	TestMPIWorld world(cfg.world_size, [argc, argv](IMPICommunicator& comm)
	{
		Run(comm, argc, argv);
	});

	world.RunAndWait();
#else
	MPI_Init(NULL, NULL);
	
	MPIWorldCommunicator comm;
		
	Run(comm, argc, argv);

	MPI_Finalize();
#endif

	return 0;
}
