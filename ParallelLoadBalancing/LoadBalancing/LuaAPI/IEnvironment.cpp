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

#include <LoadBalancing/LuaAPI/IEnvironment.h>
#include <LoadBalancing/LuaAPI/ILoadBalancingAlgorithm.h>
#include <LoadBalancing/LuaAPI/ILoadBalancingCondition.h>
#include <LoadBalancing/LuaAPI/IDomainModel.h>
#include <LoadBalancing/LuaAPI/IRebalancer.h>
#include <LoadBalancing/LuaAPI/IMPICommunicator.h>

const char* IEnvironmentMetatableName = "IEnvironment";

struct EnvironmentEntry
{
	EnvironmentDestructor destructor;
	IEnvironment*         instance;
};

#define luaLB_checkEnvironmentEntry(L, idx) \
	((EnvironmentEntry*)luaL_checkudata(L, idx, IEnvironmentMetatableName))

LUALB_API IEnvironment* luaLB_checkIEnvironment(lua_State* L, int idx)
{
	return luaLB_checkEnvironmentEntry(L, idx)->instance;
}

LUALB_API int luaLB_pushIEnvironment(lua_State* L, IEnvironment* instance, EnvironmentDestructor destructor)
{
	EnvironmentEntry* entry = (EnvironmentEntry*)lua_newuserdata(L, sizeof(EnvironmentEntry));
	entry->instance = instance;
	entry->destructor = destructor;

	lua_newtable(L);
	lua_setuservalue(L, -2);

	luaL_getmetatable(L, IEnvironmentMetatableName);
	lua_setmetatable(L, -2);

	return 1;
}

static int instance_destructor(lua_State* L)
{
	EnvironmentEntry* entry = luaLB_checkEnvironmentEntry(L, 1);
	
	entry->destructor(entry->instance);

	return 0;
}

static int instance_tostring(lua_State* L)
{
	IEnvironment* instance = luaLB_checkIEnvironment(L, 1);
	
	lua_pushstring(L, IEnvironmentMetatableName);

	return 1;
}

IDomainModel* lua_checkDomainModel(lua_State* L, int idx)
{
    lua_pushvalue(L, idx);
    lua_getfield(L, -1, "AsIDomainModel");
    lua_pushvalue(L, -2);
    lua_pcall(L, 1, 1, 0);
    IDomainModel* result = (IDomainModel*)lua_touserdata(L, -1);
    lua_pop(L, 1);

    return result;
}


static int instance_run(lua_State* L) //env:run(IMPICommunicator& comm, IDomainModel& dm, ILoadBalancingAlgorithm& lb, ILoadBalancingCondition& lbc, IRebalancer& rb)
{
	IEnvironment* pEnv = luaLB_checkIEnvironment(L, 1);
	
	if(lua_gettop(L) != 6)
	{
		luaL_error(L, "Function env:run takes 5 arguments!");
	}	
	

	IMPICommunicator* comm       = luaLB_checkIMPICommunicator(L, 2);
	IDomainModel* dm             = lua_checkDomainModel(L, 3); 
	ILoadBalancingAlgorithm* lb  = luaLB_checkILoadBalancingAlgorithm(L, 4);
	ILoadBalancingCondition* lbc = luaLB_checkILoadBalancingCondition(L, 5);
	IRebalancer* rb              = luaLB_checkIRebalancer(L, 6);

	pEnv->Run(*comm, *dm, *lb, *lbc, *rb);

	return 0;
}

static const luaL_Reg instance_functions[] = {
	{"__gc",                      instance_destructor},
	{"__tostring",                instance_tostring},
	{"run",                       instance_run},

	{NULL, NULL}
};

LUALB_API int luaLB_openIEnvironment(lua_State* L)
{
	luaL_newmetatable(L, IEnvironmentMetatableName);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, instance_functions, 0);
	lua_pop(L, 1);

	return 0;
}
