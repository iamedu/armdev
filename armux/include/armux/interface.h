#ifndef _INTERFACE_H
#define _INTERFACE_H

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

#include <stdlib.h>
#include <armux/processor.h>
#include <lua.h>
#include <lauxlib.h>

#define PROC "Proc"

static int Proc_read_reg(lua_State *L);
static int Proc_tostring(lua_State *L);

static const luaL_reg Proc_methods[] = {
	{"readReg", Proc_read_reg},
	{NULL, NULL}
};

static const luaL_reg Proc_meta[] = {
	{"__tostring", Proc_tostring},
	{NULL, NULL}
};

int Proc_register(lua_State *L);

static ARMProc **pushProc(lua_State *L, ARMProc *proc);
static ARMProc *checkProc(lua_State *L, int index);

void banner();
void interface_start(ARMProc *);
void interface_print(char *, ARMProc *);

#endif

