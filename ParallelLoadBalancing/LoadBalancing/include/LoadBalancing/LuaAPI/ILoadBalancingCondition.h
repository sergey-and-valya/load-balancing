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

#ifndef _LUAAPI_ILOADBALANCINGCONDITION_H
#define _LUAAPI_ILOADBALANCINGCONDITION_H

#include "LuaAPI.h"
#include "../ILoadBalancingCondition.h"

typedef void (*LoadBalancingConditionDestructor) (ILoadBalancingCondition* instance);

LUALB_API int luaLB_pushILoadBalancingCondition(lua_State* L, ILoadBalancingCondition* instance, LoadBalancingConditionDestructor destructor);

LUALB_API ILoadBalancingCondition* luaLB_checkILoadBalancingCondition(lua_State* L, int idx);

LUALB_API int luaLB_openILoadBalancingCondition(lua_State* L);


#endif
