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

#include <lua.hpp>

#include "StandartLuaModule/LoadBalancingAlgorithmModule.h"
#include "StandartLuaModule/LoadBalancingConditionModule.h"
#include "StandartLuaModule/RebalancerModule.h"
#include "StandartLuaModule/EnvironmentModule.h"
#include "StandartLuaModule/DomainModelModule.h"
#include "StandartLuaModule/LuaFunctionModule.h"

static int luaopen_Standart(lua_State* L)
{
	lua_newtable(L);
	
	luaopen_Standart_LoadBalancingAlgorithm(L);
	lua_setfield(L, -2, "LoadBalancingAlgorithm");
	
	luaopen_Standart_LoadBalancingCondition(L);
	lua_setfield(L, -2, "LoadBalancingCondition");
	
	luaopen_Standart_Rebalancer(L);
	lua_setfield(L, -2, "Rebalancer");
	
	luaopen_Standart_Environment(L);
	lua_setfield(L, -2, "Environment");
	
	luaopen_Standart_DomainModel(L);
	lua_setfield(L, -2, "DomainModel");
	
	luaopen_Standart_LuaFunction(L);
	lua_setfield(L, -2, "LuaFunction");
	
	return 1;
}

int lua_registerStandartModuleLoader(lua_State* L)
{
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "preload");
	lua_pushcfunction(L, luaopen_Standart);
	lua_setfield(L, -2, "Standart");
	lua_pop(L, 2);
	return 0;
}
