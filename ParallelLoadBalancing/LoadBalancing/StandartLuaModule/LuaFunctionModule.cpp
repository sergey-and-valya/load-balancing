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
#include "../LuaFunction.h"
#include "LuaFunctionModule.h"

#define METATABLE_NAME "Standart.LuaFunction"
#define luaModule_checkFunction(L) \
	((LuaFunction*)luaL_checkudata(L, 1, METATABLE_NAME))

static int luaModule_new(lua_State* L)
{
	const char* filename = lua_tostring(L, 1);
	LuaFunction* f = (LuaFunction*)lua_newuserdata(L, sizeof(LuaFunction));
	new(f) LuaFunction(filename);

	luaL_getmetatable(L, METATABLE_NAME);
	lua_setmetatable(L, -2);

	return 1;
}

static int luaModule_instance_destructor(lua_State* L)
{
	LuaFunction* f = luaModule_checkFunction(L);
	
	f->~LuaFunction();

	return 0;
}

static int luaModule_instance_tostring(lua_State* L)
{
	LuaFunction* f = luaModule_checkFunction(L);
	
	lua_pushstring(L, METATABLE_NAME);

	return 1;
}

static int luaModule_instance_AsIFunction(lua_State* L)
{
	LuaFunction* f = luaModule_checkFunction(L);
	
	lua_pushlightuserdata(L, static_cast<IFunction*>(f));

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

	{"AsIFunction",               luaModule_instance_AsIFunction},

	{NULL, NULL}
};

int luaopen_Standart_LuaFunction(lua_State* L)
{
	luaL_newmetatable(L, METATABLE_NAME);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, module_instance_functions, 0);
	lua_pop(L, 1);
	luaL_newlib(L, module_functions);
	return 1;
}
