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

#include <LoadBalancing/LuaAPI/IRebalancer.h>
#include "../Rebalancer.h"
#include "RebalancerModule.h"

static int luaModule_new(lua_State* L)
{
	luaLB_pushIRebalancer(L, new Rebalancer());

	return 1;
}

static const luaL_Reg module_functions[] = {
	{"new", luaModule_new},
	{NULL,  NULL}
};

int luaopen_Standart_Rebalancer(lua_State* L)
{
	luaL_newlib(L, module_functions);
	return 1;
}