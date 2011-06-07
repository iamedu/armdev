/*
 * Copyright 2009 armux authors.
 *
 * This file is part of armux.
 *
 * armux is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * armux is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with armux.  If not, see <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include <armux/interface.h>
#include <armux/processor.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <lua.h>
#include <lauxlib.h>

void banner() {
	printf("armux ARM simulator\n");
}

void interface_start(ARMProc *proc) {
	char *command;
	lua_State *L;
	int status;
	ARMProc **ptr;

	L = luaL_newstate();
	luaL_openlibs(L);

	Proc_register(L);

	pushProc(L, proc);
	lua_setglobal(L, "proc");


	while(1) {
		command = readline("(armux)>> ");
		status = luaL_dostring(L, command);
		add_history(command);

		
		if(status) {
			fprintf(stderr, "An error occured: %s\n",
				lua_tostring(L, -1));
		}
	}
}

static int Proc_read_reg(lua_State *L) {
	ARMProc *proc;
	int **reg_ptr;
	int reg;
	proc = checkProc(L, 1);
	reg  = luaL_checkint(L, 2);
	reg_ptr = &proc->r0;
	reg_ptr += reg;
	lua_pushnumber(L, **reg_ptr);
	return 1;
}

static int Proc_tostring(lua_State *L) {
	lua_pushfstring(L, "Soy un procesador");
	return 1;
}

int Proc_register(lua_State *L) {
	luaL_openlib(L, PROC, Proc_methods, 0);
	luaL_newmetatable(L, PROC);
	luaL_openlib(L, 0, Proc_meta, 0);
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);
	return 1;
}

static ARMProc **pushProc(lua_State *L, ARMProc *proc) {
	ARMProc **ptr = (ARMProc **)lua_newuserdata(L, sizeof(ARMProc *));
	*ptr = proc;
	luaL_getmetatable(L, PROC);
	lua_setmetatable(L, -2);
	return ptr;
}

static ARMProc *checkProc(lua_State *L, int index) {
	ARMProc **ptr, *proc;
	luaL_checktype(L, index, LUA_TUSERDATA);
	ptr = (ARMProc **)luaL_checkudata(L, index, PROC);
	if(ptr == NULL) luaL_typerror(L, index, PROC);
	proc = *ptr;
	if(!proc)
            luaL_error(L, "null Processor");
	return proc;
}

