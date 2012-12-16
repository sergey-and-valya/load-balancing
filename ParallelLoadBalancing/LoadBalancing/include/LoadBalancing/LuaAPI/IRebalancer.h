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

#ifndef _LUAAPI_IREBALANCER_H
#define _LUAAPI_IREBALANCER_H

#include "LuaAPI.h"
#include "../IRebalancer.h"

typedef void (*RebalancerDestructor) (IRebalancer* instance);

LUALB_API int luaLB_pushIRebalancer(lua_State* L, IRebalancer* instance, RebalancerDestructor destructor);

LUALB_API IRebalancer* luaLB_checkIRebalancer(lua_State* L, int idx);

LUALB_API int luaLB_openIRebalancer(lua_State* L);


#endif
