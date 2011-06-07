#include <config.h>
#include <stdio.h>
#include <string.h>

#include <armux/processor.h>
#include <armux/lua.h>

// Check if has python for interactive shell
#ifdef PYTHON
#include <Python.h>
#else

//If not use included lua
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#endif

// Check if has readline
#ifdef HAVE_LIBREADLINE

#include <readline/readline.h>
#include <readline/history.h>

#endif

#define PROMPT "armux>> "

void banner() {
	printf("%s simulator version %s\n", PACKAGE, VERSION);
}

void ishell(ThreadParams *params) {
	banner();
	char *command;
	int status;

#ifndef PYTHON
	lua_State *L;
#endif

#ifndef HAVE_LIBREADLINE
	command = malloc(250);
#endif

#ifdef PYTHON
	Py_Initialize();
	Py_Main(0, NULL);
	Py_Finalize();
#else
	L = luaL_newstate();
	luaL_openlibs(L);

	Proc_register(L);
	pushProc(L, params->proc);
	lua_setglobal(L, "proc");

	add_history("proc:writeReg(15,0x8000)");
	add_history("proc:resume()");


	while(1) {
#ifdef HAVE_LIBREADLINE
		command = readline(PROMPT);
		if(strcmp(command, "") != 0) {
			add_history(command);
		}
#else
		printf(PROMPT);
		scanf("%s", command);
#endif
		if(strcmp(command, "exit") == 0) {
			break;
		}
		status = luaL_dostring(L, command);
		if(status) {
			fprintf(stderr, "An error occured: %s\n",
			lua_tostring(L, -1));
		}
	}
#endif


}

