#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <armux/processor.h>

#include <argp.h>
#include <config.h>

const char *argp_program_version =
    PACKAGE_STRING;

const char *argp_program_bug_address = 
    PACKAGE_BUGREPORT;

static char doc[] =
    "armux es un simulador muy sencillo de arm";

static char args_doc[] = "ARM_FILE";

static struct argp_option options[] = {
	//{"verbose",  'v', 0,      0,  "Produce verbose output" },
	{ 0 }
};

struct arguments {
	char *args[1];
};

static error_t parse_opt (int, char *, struct argp_state *);

static struct argp argp = {options, parse_opt, args_doc, doc};

void ishell(ThreadParams *);

#endif

