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

#include <LoadBalancing/LuaAPI/IDomainModel.h>

const char* IDomainModelMetatableName = "IDomainModel";

LUALB_API int luaLB_pushIDomainModel(lua_State* L, IDomainModel* instance)
{
	IDomainModel** pinstance = (IDomainModel**)lua_newuserdata(L, sizeof(IDomainModel*));
	*pinstance = instance;

	lua_newtable(L);
	lua_setuservalue(L, -2);

	luaL_getmetatable(L, IDomainModelMetatableName);
	lua_setmetatable(L, -2);

	return 1;
}

static int instance_destructor(lua_State* L)
{
	IDomainModel** pinstance = luaLB_checkIDomainModel(L, 1);
	
	delete *pinstance;

	return 0;
}

static int instance_tostring(lua_State* L)
{
	IDomainModel** pinstance = luaLB_checkIDomainModel(L, 1);
	
	lua_pushstring(L, IDomainModelMetatableName);

	return 1;
}

static const luaL_Reg instance_functions[] = {
	{"__gc",                      instance_destructor},
	{"__tostring",                instance_tostring},

	{NULL, NULL}
};

LUALB_API int luaLB_openIDomainModel(lua_State* L)
{
	luaL_newmetatable(L, IDomainModelMetatableName);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, instance_functions, 0);
	lua_pop(L, 1);

	return 0;
}
