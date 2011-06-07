#include <armux/lua.h>

static const luaL_reg Proc_methods[] = {
        {"readReg", Proc_read_reg},
        {"readMem", Proc_read_mem},
        {"writeReg", Proc_write_reg},
        {"writeMem", Proc_read_mem},
        {"resume", Proc_resume},
        {"step", Proc_step},
        {"pause", Proc_pause},
        {NULL, NULL}
};

static const luaL_reg Proc_meta[] = {
        {"__tostring", Proc_tostring},
        {NULL, NULL}
};

static int Proc_step(lua_State *L) {
        ARMProc *proc;
        int value;
        int reg;
        proc = checkProc(L, 1);
	step(proc->thread);
        return 0;
}

static int Proc_resume(lua_State *L) {
        ARMProc *proc;
        int value;
        int reg;
        proc = checkProc(L, 1);
	resumeExecution(proc, proc->thread);
        return 0;
}

static int Proc_pause(lua_State *L) {
        ARMProc *proc;
        int value;
        int reg;
        proc = checkProc(L, 1);
	pauseExecution(proc, proc->thread);
        return 0;
}

static int Proc_read_reg(lua_State *L) {
        ARMProc *proc;
        int value;
        int reg;
        proc = checkProc(L, 1);
        reg  = luaL_checkint(L, 2);
	value = *proc->r[reg];
        lua_pushnumber(L, value);
        return 1;
}


static int Proc_write_reg(lua_State *L) {
        ARMProc *proc;
        int value;
        int reg;
        proc = checkProc(L, 1);
        reg  = luaL_checkint(L, 2);
        value = luaL_checkint(L, 3);
	*proc->r[reg] = value;
        return 1;
}

static int Proc_read_mem(lua_State *L) {
        ARMProc *proc;
        int value;
        int addr;
        proc = checkProc(L, 1);
        addr = luaL_checkint(L, 2);
	value = proc->readWord(proc, addr);
        lua_pushnumber(L, value);
        return 1;
}

static int Proc_write_mem(lua_State *L) {
        ARMProc *proc;
        int value;
        int addr;
        proc = checkProc(L, 1);
        addr = luaL_checkint(L, 2);
        value = luaL_checkint(L, 3);
	proc->writeWord(proc, addr, value);
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

ARMProc **pushProc(lua_State *L, ARMProc *proc) {
        ARMProc **ptr = (ARMProc **)lua_newuserdata(L, sizeof(ARMProc *));
        *ptr = proc;
        luaL_getmetatable(L, PROC);
        lua_setmetatable(L, -2);
        return ptr;
}

ARMProc *checkProc(lua_State *L, int index) {
        ARMProc **ptr, *proc;
        luaL_checktype(L, index, LUA_TUSERDATA);
        ptr = (ARMProc **)luaL_checkudata(L, index, PROC);
        if(ptr == NULL) luaL_typerror(L, index, PROC);
        proc = *ptr;
        if(!proc)
            luaL_error(L, "null Processor");
        return proc;
}

