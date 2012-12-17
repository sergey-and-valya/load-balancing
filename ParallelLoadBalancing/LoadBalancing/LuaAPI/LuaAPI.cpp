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
#include <LoadBalancing/LuaAPI/ILoadBalancingCondition.h>
#include <LoadBalancing/LuaAPI/IRebalancer.h>
#include <LoadBalancing/LuaAPI/IEnvironment.h>
#include <LoadBalancing/LuaAPI/IDomainModel.h>
#include <LoadBalancing/LuaAPI/IMPICommunicator.h>

LUALB_API int luaLB_openlibs(lua_State* L)
{
	luaLB_openILoadBalancingAlgorithm(L);
	luaLB_openILoadBalancingCondition(L);
	luaLB_openIRebalancer(L);
	luaLB_openIEnvironment(L);
	luaLB_openIDomainModel(L);
	luaLB_openIMPICommunicator(L);

	return 0;
}
