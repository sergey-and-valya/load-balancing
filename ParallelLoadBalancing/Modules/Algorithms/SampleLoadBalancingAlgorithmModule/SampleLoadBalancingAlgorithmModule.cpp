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
#include "SampleLoadBalancingAlgorithm.h"

static int luaModule_new(lua_State* L)
{
	int parameter1 = luaL_checkinteger(L, 1);
	int parameter2 = luaL_checkinteger(L, 2);

	luaLB_pushILoadBalancingAlgorithm(L, new SampleLoadBalancingAlgorithm(parameter1, parameter2));

	return 1;
}

static const luaL_Reg module_functions[] = {
	{"new", luaModule_new},
	{NULL,  NULL}
};

extern "C" __declspec(dllexport) int luaopen_SampleLoadBalancingAlgorithmModule(lua_State* L)
{
	luaL_newlib(L, module_functions);
	return 1;
}

int main()
{
	//do nothing
}

