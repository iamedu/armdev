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
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <libconfig.h>
#include <armux/processor.h>
#include <armux/instruction.h>
#include <armux/addressing.h>
#include <armux/utils.h>
#include <armux/memory.h>
#include <armux/devices.h>

void proc_loop(void *ptr) {
	ARMProc *p = (ARMProc *)ptr;
	int i;
	int inst;
	while(1) {
		printf("%x ", *p->pc);
		inst = fetch(p);
		printf("%x ", inst);
		for(i = 0; i < INSTRUCTION_NUMBER; i++) {
			if(test_inst(insts[i], inst)) {
				printf(" executed %d\n", i);
				(*insts[i]->execute)(inst, p);
				break;
			}
		}
	}
}

void setup(ARMProc *p) {
	int i;
	config_t config;
	config_setting_t *mem;
	config_setting_t *m;
	config_setting_t *load;
	config_setting_t *l;
	long start;
	long size;
	long location;
	int mem_size;
	int load_size;
	char *type;
	char *file;
	ARMMem *memory;
	FILE *in;
	char buf;

	config_init(&config);

	if(config_read_file(&config, "armux.cfg") == CONFIG_FALSE) {
		fprintf(stderr, "Error %s\n", config_error_text(&config));
		config_destroy(&config);
		exit(1);
	}

	if(config_lookup_int(&config, "armux.start", &start) == CONFIG_FALSE) {
		fprintf(stderr, "Error %s\n", config_error_text(&config));
		config_destroy(&config);
		exit(1);
	}

	start = start & 0xffffffff;

	*p->pc = start;

	mem = config_lookup(&config, "armux.memory");


	if(mem == NULL) {
		fprintf(stderr, "Error %s\n", config_error_text(&config));
		config_destroy(&config);
		exit(1);
	}

	mem_size = config_setting_length(mem);
	memory = init_memory(mem_size);


	for(i = 0; i < mem_size; i++) {
		m = config_setting_get_elem(mem, i);
		if(m == NULL) {
			fprintf(stderr, "Error %s\n", config_error_text(&config));
			config_destroy(&config);
			exit(1);
		}
		config_setting_lookup_string(m, "type", &type);
		config_setting_lookup_int(m, "location", &location);
		if(strcmp(type, "internal") == 0) {
			config_setting_lookup_int(m, "size", &size);
			memory->entries[i] = init_phys_memory(location, size);
		} else if(strcmp(type, "usart") == 0) {
			memory->entries[i] = init_usart_device(location);
		}
	}

	p->memory = memory;

	load = config_lookup(&config, "armux.load");
	load_size = config_setting_length(load);

	for(i = 0; i < load_size; i++) {
		l = config_setting_get_elem(load, i);
		if(l == NULL) {
			fprintf(stderr, "Error %s\n", config_error_text(&config));
			config_destroy(&config);
			exit(1);
		}
		config_setting_lookup_int(l, "location", &location);
		config_setting_lookup_string(l, "file", &file);
		in = fopen(file, "r");

		if(in == NULL) {
			perror("Error");
			exit(1);
		}

		while(fread(&buf, 1, 1, in) > 0) {
			write_mem(p, i++, 1, buf);
		}

		fclose(in);
	}

	config_destroy(&config);
}

int main(int argc, char **argv) {
	ARMProc *p = create_proc();
	pthread_t proc_thread;
	int proc_id;
	char buf;
	int i = 0;

	insts = inst_dict();

	banner();
	setup(p);

	proc_id = pthread_create(&proc_thread, NULL, (void *)proc_loop, 
			(void *)p);

	interface_start(p);

	pthread_join(proc_thread, NULL);

	return 0;
}

