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

#ifndef _LUAAPI_IENVIRONMENT_H
#define _LUAAPI_IENVIRONMENT_H

#include "LuaAPI.h"
#include "../IEnvironment.h"

typedef void (*EnvironmentDestructor) (IEnvironment* instance);

LUALB_API int luaLB_pushIEnvironment(lua_State* L, IEnvironment* instance, EnvironmentDestructor destructor);

LUALB_API IEnvironment* luaLB_checkIEnvironment(lua_State* L, int idx);

LUALB_API int luaLB_openIEnvironment(lua_State* L);


#endif
