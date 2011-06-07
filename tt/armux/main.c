#include <stdio.h>
#include <stdlib.h>
#include <argp.h>

#include <armux/program.h>
#include <armux/types.h>
#include <armux/processor.h>
#include <armux/instruction.h>

static error_t parse_opt (int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = state->input;

  switch (key) {
    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
	{
	  argp_usage(state);
	}
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 1)
	{
	  argp_usage (state);
	}
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

int main(int argc, char **argv) {
	ARMProc *proc = init();
	ConnectsServer connectsServer;
	struct arguments arguments;
	ThreadParams *params;
	FILE *pidFile;
	ARMInst *root = instruction_set();
	char **new_argv;
	char *command;
	int status;

	new_argv = malloc(sizeof(int *) * 2);
	new_argv[0] = argv[0];
	new_argv[1] = NULL;

	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	connectsServer.running = 1;
	connectsServer.proc = proc;

	pidFile = fopen("/tmp/armux", "w");
	fprintf(pidFile, "%d", getpid());
	fclose(pidFile);

	initConnectsServer(&connectsServer);

	loadProgram(proc, arguments.args[0]);

	params = startExecution(proc, root);

	ishell(params);

	connectsServer.running = 0;
	pthread_cancel(connectsServer.thread);
	stopExecution(proc, params);


	return 0;
}

