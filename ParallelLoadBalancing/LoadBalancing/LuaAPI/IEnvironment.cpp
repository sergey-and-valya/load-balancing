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

const char* IEnvironmentMetatableName = "IEnvironment";

LUALB_API int luaLB_pushIEnvironment(lua_State* L, IEnvironment* instance)
{
	IEnvironment** pinstance = (IEnvironment**)lua_newuserdata(L, sizeof(IEnvironment*));
	*pinstance = instance;

	lua_newtable(L);
	lua_setuservalue(L, -2);

	luaL_getmetatable(L, IEnvironmentMetatableName);
	lua_setmetatable(L, -2);

	return 1;
}

static int instance_destructor(lua_State* L)
{
	IEnvironment** pinstance = luaLB_checkIEnvironment(L, 1);
	
	delete *pinstance;

	return 0;
}

static int instance_tostring(lua_State* L)
{
	IEnvironment** pinstance = luaLB_checkIEnvironment(L, 1);
	
	lua_pushstring(L, IEnvironmentMetatableName);

	return 1;
}

static const luaL_Reg instance_functions[] = {
	{"__gc",                      instance_destructor},
	{"__tostring",                instance_tostring},

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
