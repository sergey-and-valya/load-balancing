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

#ifndef _LUAAPI_IDOMAINMODEL_H
#define _LUAAPI_IDOMAINMODEL_H

#include "LuaAPI.h"
#include "../IDomainModel.h"

LUALB_API extern const char* IDomainModelMetatableName;

#define luaLB_checkIDomainModel(L, idx) \
	((IDomainModel**)luaL_checkudata(L, idx, IDomainModelMetatableName))

LUALB_API int luaLB_pushIDomainModel(lua_State* L, IDomainModel* instance);

LUALB_API int luaLB_openIDomainModel(lua_State* L);


#endif
