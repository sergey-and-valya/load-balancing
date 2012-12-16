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

#include <LoadBalancing/LuaAPI/ILoadBalancingAlgorithm.h>

const char* ILoadBalancingAlgorithmMetatableName = "ILoadBalancingAlgorithm";

struct LoadBalancingAlgorithmEntry
{
	LoadBalancingAlgorithmDestructor destructor;
	ILoadBalancingAlgorithm*         instance;
};

#define luaLB_checkLoadBalancingAlgorithmEntry(L, idx) \
	((LoadBalancingAlgorithmEntry*)luaL_checkudata(L, idx, ILoadBalancingAlgorithmMetatableName))

LUALB_API ILoadBalancingAlgorithm* luaLB_checkILoadBalancingAlgorithm(lua_State* L, int idx)
{
	return luaLB_checkLoadBalancingAlgorithmEntry(L, idx)->instance;
}

LUALB_API int luaLB_pushILoadBalancingAlgorithm(lua_State* L, ILoadBalancingAlgorithm* instance, LoadBalancingAlgorithmDestructor destructor)
{
	LoadBalancingAlgorithmEntry* entry = (LoadBalancingAlgorithmEntry*)lua_newuserdata(L, sizeof(LoadBalancingAlgorithmEntry));
	entry->instance = instance;
	entry->destructor = destructor;

	lua_newtable(L);
	lua_setuservalue(L, -2);

	luaL_getmetatable(L, ILoadBalancingAlgorithmMetatableName);
	lua_setmetatable(L, -2);

	return 1;
}

static int instance_destructor(lua_State* L)
{
	LoadBalancingAlgorithmEntry* entry = luaLB_checkLoadBalancingAlgorithmEntry(L, 1);
	
	entry->destructor(entry->instance);

	return 0;
}

static int instance_tostring(lua_State* L)
{
	ILoadBalancingAlgorithm* instance = luaLB_checkILoadBalancingAlgorithm(L, 1);
	
	lua_pushstring(L, ILoadBalancingAlgorithmMetatableName);

	return 1;
}

static const luaL_Reg instance_functions[] = {
	{"__gc",                      instance_destructor},
	{"__tostring",                instance_tostring},

	{NULL, NULL}
};

LUALB_API int luaLB_openILoadBalancingAlgorithm(lua_State* L)
{
	luaL_newmetatable(L, ILoadBalancingAlgorithmMetatableName);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, instance_functions, 0);
	lua_pop(L, 1);

	return 0;
}
