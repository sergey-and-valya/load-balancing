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

#include "LuaFunction.h"

// [-3, +1, -] number value(Values* values, int i, int j)
static int luaLB_Value(lua_State* lua)
{
	Values* values = (Values*) lua_touserdata(lua, -3);
	int i = lua_tointeger(lua, -2);
	int j = lua_tointeger(lua, -1);

	lua_pushnumber(lua, values->Value(i - 1, j - 1));
	return 1;
}

// [-3, +1, -] bool has_value(Values* values, int i, int j)
static int luaLB_HasValue(lua_State* lua)
{
	Values* values = (Values*) lua_touserdata(lua, -3);
	int i = lua_tointeger(lua, -2);
	int j = lua_tointeger(lua, -1);

	lua_pushboolean(lua, values->HasValue(i - 1, j - 1));
	return 1;
}

LuaFunction::LuaFunction(std::string filename)
{
	lua = luaL_newstate();
	luaL_openlibs(lua);

	//register HasValue() and Value() for lua scripts
	lua_pushcfunction(lua, luaLB_Value);
	lua_setglobal(lua, "value");

	lua_pushcfunction(lua, luaLB_HasValue);
	lua_setglobal(lua, "has_value");

	if(luaL_loadfile(lua, filename.c_str()))
	{
		printf("function file '%s' is not found\n", filename.c_str());
		exit(1);
	}

	if(lua_pcall(lua, 0, 0, 0))
	{
		printf("ERROR in executing function file :  %s\n", lua_tostring(lua, -1));
		exit(1);
	}
}

LuaFunction::~LuaFunction()
{
	lua_close(lua); 
}

double LuaFunction::operator()(const Values& values, int i, int j)
{
	lua_getglobal(lua, "func");
	lua_pushlightuserdata(lua, (void*) &values);
	lua_pushinteger(lua, i);
	lua_pushinteger(lua, j);

	if(lua_pcall(lua, 3, 1, 0))
	{
		printf("ERROR in function call:\n%s\n", lua_tostring(lua, -1));
		exit(1);
	}

	return lua_tonumber(lua, -1);
}