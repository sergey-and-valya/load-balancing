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

#include <LoadBalancing/LuaAPI/ILoadBalancingCondition.h>

const char* ILoadBalancingConditionMetatableName = "ILoadBalancingCondition";

struct LoadBalancingConditionEntry
{
	LoadBalancingConditionDestructor destructor;
	ILoadBalancingCondition*         instance;
};

#define luaLB_checkLoadBalancingConditionEntry(L, idx) \
	((LoadBalancingConditionEntry*)luaL_checkudata(L, idx, ILoadBalancingConditionMetatableName))

LUALB_API ILoadBalancingCondition* luaLB_checkILoadBalancingCondition(lua_State* L, int idx)
{
	return luaLB_checkLoadBalancingConditionEntry(L, idx)->instance;
}

LUALB_API int luaLB_pushILoadBalancingCondition(lua_State* L, ILoadBalancingCondition* instance, LoadBalancingConditionDestructor destructor)
{
	LoadBalancingConditionEntry* entry = (LoadBalancingConditionEntry*)lua_newuserdata(L, sizeof(LoadBalancingConditionEntry));
	entry->instance = instance;
	entry->destructor = destructor;

	lua_newtable(L);
	lua_setuservalue(L, -2);

	luaL_getmetatable(L, ILoadBalancingConditionMetatableName);
	lua_setmetatable(L, -2);

	return 1;
}

static int instance_destructor(lua_State* L)
{
	LoadBalancingConditionEntry* entry = luaLB_checkLoadBalancingConditionEntry(L, 1);
	
	entry->destructor(entry->instance);

	return 0;
}

static int instance_tostring(lua_State* L)
{
	ILoadBalancingCondition* instance = luaLB_checkILoadBalancingCondition(L, 1);
	
	lua_pushstring(L, ILoadBalancingConditionMetatableName);

	return 1;
}

static const luaL_Reg instance_functions[] = {
	{"__gc",                      instance_destructor},
	{"__tostring",                instance_tostring},

	{NULL, NULL}
};

LUALB_API int luaLB_openILoadBalancingCondition(lua_State* L)
{
	luaL_newmetatable(L, ILoadBalancingConditionMetatableName);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, instance_functions, 0);
	lua_pop(L, 1);

	return 0;
}
