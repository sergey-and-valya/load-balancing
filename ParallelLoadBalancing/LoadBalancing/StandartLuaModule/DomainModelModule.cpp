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
#include "../DomainModel.h"
#include "../BinaryFile.h"
#include "DomainModelModule.h"

#define METATABLE_NAME "Standart.DomainModel"
#define luaModule_checkDomainModelWithFile(L) \
	((DomainModelWithFile*)luaL_checkudata(L, 1, METATABLE_NAME))

class DomainModelWithFile
{
public:
	DomainModel dm;
	BinaryFile bf;
};

IFunction* lua_checkFunction(lua_State* L)
{
	lua_getfield(L, -1, "AsIFunction");
	lua_pushvalue(L, -2);
	lua_pcall(L, 1, 1, 0);
	return (IFunction*)lua_touserdata(L, -1);
}

static int luaModule_new(lua_State* L)
{
	const char* filename = lua_tostring(L, 1);
	int steps = lua_tointeger(L, 3);
	//check if argument #2 is IFunction
	lua_pushvalue(L, 2);
	IFunction* func = lua_checkFunction(L);
	lua_pop(L, 2);
	
	DomainModelWithFile* dmwf = (DomainModelWithFile*)lua_newuserdata(L, sizeof(DomainModelWithFile));
	new(&(dmwf->bf)) BinaryFile(filename);
	new(&(dmwf->dm)) DomainModel(dmwf->bf, *func, steps);
	
	lua_newtable(L);
	lua_pushvalue(L, 2);
	lua_setfield(L, -2, "function");
	lua_setuservalue(L, -2);

	luaL_getmetatable(L, METATABLE_NAME);
	lua_setmetatable(L, -2);

	return 1;
}

static int luaModule_instance_destructor(lua_State* L)
{
	DomainModelWithFile* dmwf = luaModule_checkDomainModelWithFile(L);
	
	dmwf->dm.~DomainModel();
	dmwf->bf.~BinaryFile();

	return 0;
}

static int luaModule_instance_tostring(lua_State* L)
{
	DomainModelWithFile* dmwf = luaModule_checkDomainModelWithFile(L);
	
	lua_pushstring(L, METATABLE_NAME);

	return 1;
}

static int luaModule_instance_AsIDomainModel(lua_State* L)
{
	DomainModelWithFile* dmwf = luaModule_checkDomainModelWithFile(L);
	
	lua_pushlightuserdata(L, static_cast<IDomainModel*>(&(dmwf->dm)));

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

	{"AsIDomainModel",            luaModule_instance_AsIDomainModel},

	{NULL, NULL}
};

int luaopen_Standart_DomainModel(lua_State* L)
{
	luaL_newmetatable(L, METATABLE_NAME);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, module_instance_functions, 0);
	lua_pop(L, 1);
	luaL_newlib(L, module_functions);
	return 1;
}
