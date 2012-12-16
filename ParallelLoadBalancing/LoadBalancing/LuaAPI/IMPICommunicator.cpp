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

#include <LoadBalancing/LuaAPI/IMPICommunicator.h>

const char* IMPICommunicatorMetatableName = "IMPICommunicator";

struct MPICommunicatorEntry
{
	MPICommunicatorDestructor destructor;
	IMPICommunicator*         instance;
};

#define luaLB_checkMPICommunicatorEntry(L, idx) \
	((MPICommunicatorEntry*)luaL_checkudata(L, idx, IMPICommunicatorMetatableName))

LUALB_API IMPICommunicator* luaLB_checkIMPICommunicator(lua_State* L, int idx)
{
	return luaLB_checkMPICommunicatorEntry(L, idx)->instance;
}

LUALB_API int luaLB_pushIMPICommunicator(lua_State* L, IMPICommunicator* instance, MPICommunicatorDestructor destructor)
{
	MPICommunicatorEntry* entry = (MPICommunicatorEntry*)lua_newuserdata(L, sizeof(MPICommunicatorEntry));
	entry->instance = instance;
	entry->destructor = destructor;

	lua_newtable(L);
	lua_setuservalue(L, -2);

	luaL_getmetatable(L, IMPICommunicatorMetatableName);
	lua_setmetatable(L, -2);

	return 1;
}

static int instance_destructor(lua_State* L)
{
	MPICommunicatorEntry* entry = luaLB_checkMPICommunicatorEntry(L, 1);
	
	entry->destructor(entry->instance);

	return 0;
}

static int instance_tostring(lua_State* L)
{
	IMPICommunicator* instance = luaLB_checkIMPICommunicator(L, 1);
	
	lua_pushstring(L, IMPICommunicatorMetatableName);

	return 1;
}

static const luaL_Reg instance_functions[] = {
	{"__gc",                      instance_destructor},
	{"__tostring",                instance_tostring},

	{NULL, NULL}
};

LUALB_API int luaLB_openIMPICommunicator(lua_State* L)
{
	luaL_newmetatable(L, IMPICommunicatorMetatableName);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, instance_functions, 0);
	lua_pop(L, 1);

	return 0;
}


		//int fake_buff;
		//MPI_Status status;
		//if(rank == 0)
		//{
		//	int size;
		//	comm.Size(&size);
		//	for(int i = 1; i < size; i++)
		//	{
		//		comm.Recv(&fake_buff, 1, MPI_INT, i, 0, &status);
		//	}
		//}
		//else
		//{
		//	comm.Send(&fake_buff, 1, MPI_INT, 0, 0);
		//}