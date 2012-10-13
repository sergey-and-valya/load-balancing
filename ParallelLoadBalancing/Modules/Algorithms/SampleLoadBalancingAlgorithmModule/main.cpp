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

#include <new>
#include <lua.hpp>
#include <LoadBalancing/ILoadBalancingAlgorithm.h>
#include "SampleLoadBalancingAlgorithm.h"

#define METATABLE_NAME "SampleLoadBalancingAlgorithmModule.SampleLoadBalancingAlgorithm"
#define luaModule_checkLBA(L) \
	((SampleLoadBalancingAlgorithm*)luaL_checkudata(L, 1, METATABLE_NAME))

static int luaModule_new(lua_State* L)
{
	int parameter1 = luaL_checkinteger(L, 1);
	int parameter2 = luaL_checkinteger(L, 2);

	SampleLoadBalancingAlgorithm* lba = (SampleLoadBalancingAlgorithm*)lua_newuserdata(L, sizeof(SampleLoadBalancingAlgorithm));
	new(lba) SampleLoadBalancingAlgorithm(parameter1, parameter2);

	luaL_getmetatable(L, METATABLE_NAME);
	lua_setmetatable(L, -2);

	return 1;
}

static int luaModule_instance_destructor(lua_State* L)
{
	SampleLoadBalancingAlgorithm* lba = luaModule_checkLBA(L);
	
	lba->~SampleLoadBalancingAlgorithm();

	return 0;
}

static int luaModule_instance_tostring(lua_State* L)
{
	SampleLoadBalancingAlgorithm* lba = luaModule_checkLBA(L);
	
	lua_pushstring(L, METATABLE_NAME);

	return 1;
}

static int luaModule_instance_AsILoadBalancingAlgorithm(lua_State* L)
{
	SampleLoadBalancingAlgorithm* lba = luaModule_checkLBA(L);
	
	lua_pushlightuserdata(L, static_cast<ILoadBalancingAlgorithm*>(lba));

	return 1;
}

//static module functions:
static const luaL_Reg module_functions[] = {
	{"new", luaModule_new},
	{NULL,  NULL}
};

//member functions:
static const luaL_Reg module_instance_functions[] = {
	{"__gc",                      luaModule_instance_destructor},
	{"__tostring",                luaModule_instance_tostring},

	{"AsILoadBalancingAlgorithm", luaModule_instance_AsILoadBalancingAlgorithm},

	{NULL, NULL}
};

extern "C" __declspec(dllexport) int luaopen_SampleLoadBalancingAlgorithmModule(lua_State* L)
{
	luaL_newmetatable(L, METATABLE_NAME);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, module_instance_functions, 0);
	luaL_newlib(L, module_functions);
	return 1;
}

int main()
{
	//do nothing
}

