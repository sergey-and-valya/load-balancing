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
#include "LoadBalancingAlgorithm.h"

#define METATABLE_NAME "InitialAlgorithm.LoadBalancingAlgorithm"
#define luaL_checkLBA(L) \
	((LoadBalancingAlgorithm*)luaL_checkudata(L, 1, METATABLE_NAME))

static int luaIA_new(lua_State* L)
{
	int accuracy = luaL_checkinteger(L, -1);

	LoadBalancingAlgorithm* lba = (LoadBalancingAlgorithm*)lua_newuserdata(L, sizeof(LoadBalancingAlgorithm));
	new(lba) LoadBalancingAlgorithm(accuracy);

	luaL_getmetatable(L, METATABLE_NAME);
	lua_setmetatable(L, -2);

	return 1;
}

static int luaIA_LBA_destructor(lua_State* L)
{
	LoadBalancingAlgorithm* lba = luaL_checkLBA(L);
	
	lba->~LoadBalancingAlgorithm();

	return 0;
}

static int luaIA_LBA_tostring(lua_State* L)
{
	LoadBalancingAlgorithm* lba = luaL_checkLBA(L);
	
	lua_pushfstring(L, "InitialAlgorithm.LoadBalancingAlgorithm");

	return 0;
}

static int luaIA_LBA_ToLoadBalancingAlgorithm(lua_State* L)
{
	LoadBalancingAlgorithm* lba = luaL_checkLBA(L);
	
	lua_pushlightuserdata(L, static_cast<ILoadBalancingAlgorithm*>(lba));

	return 1;
}

//static module functions:
static const luaL_Reg InitialAlgorithm[] = {
	{"new", luaIA_new},
	{NULL, NULL}
};

//LoadBalancing member functions:
static const luaL_Reg InitialAlgorithm_LoadBalancingAlgorithm[] = {
	{"__gc",       luaIA_LBA_destructor},
	{"__tostring", luaIA_LBA_tostring},

	{"ToLoadBalancingAlgorithm", luaIA_LBA_ToLoadBalancingAlgorithm},

	{NULL, NULL}
};

extern "C" __declspec(dllexport) int luaopen_InitialAlgorithm(lua_State* L)
{
	luaL_newmetatable(L, METATABLE_NAME);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, InitialAlgorithm_LoadBalancingAlgorithm, 0);
	luaL_newlib(L, InitialAlgorithm);
	return 1;
}

int main()
{
	//do nothing
}

