#ifndef _ARMUX_LUA_H
#define _ARMUX_LUA_H

#include <lua.h>
#include <lauxlib.h>

#include <armux/processor.h>

#define PROC "Proc"

//Processor methods
static int Proc_read_reg(lua_State *);
static int Proc_read_mem(lua_State *);
static int Proc_write_reg(lua_State *);
static int Proc_write_mem(lua_State *);
static int Proc_resume(lua_State *);
static int Proc_pause(lua_State *);
static int Proc_step(lua_State *);
static int Proc_tostring(lua_State *);


int Proc_register(lua_State *L);

ARMProc **pushProc(lua_State *L, ARMProc *proc);
ARMProc *checkProc(lua_State *, int);


#endif

