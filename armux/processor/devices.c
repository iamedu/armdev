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


#include <armux/utils.h>
#include <armux/devices.h>
#include <pthread.h>
#include <pty.h>
#include <stdlib.h>
#include <unistd.h>

int uart_send_enabled(ARMUsartDevice *dev) {
	int *mem = dev->memory;
	return getbit(*mem, 6) && !getbit(*mem, 7);
}

void uart_loop(ARMUsartDevice *dev) {
	char value;
	int *extra_fd = (int *)dev->extra;
	while(1) {
		while(!uart_send_enabled(dev));
		while(getbit(dev->memory[0x0014], 1));
		value = dev->memory[0x001c];
		dev->memory[0x001c] = 0;
		write(extra_fd[0], &value, 1);
		dev->memory[0x0014] = setbit(dev->memory[0x0014], 1, 1);
	}
}

ARMUsartDevice *init_usart_device(unsigned int location) {
	int size = 0x4000;
	int *extra_fd;
	pthread_t t;

	ARMUsartDevice *entry = malloc(sizeof(ARMUsartDevice));
	entry->location = location;
	entry->size = size;
	entry->type = USART;
	entry->memory = malloc(size);
	entry->read_memory  = read_usart_device;
	entry->write_memory = write_usart_device;

	//Memory initializations
	entry->memory[0x0014] = 2;

	extra_fd = malloc(sizeof(int) * 2);

	if(openpty(&extra_fd[0], &extra_fd[1], NULL, NULL, NULL) == -1) {
		perror("USART Error");
	} else {
		printf("Setting up serial port 0x%x at %s\n",
			location,
			ptsname(extra_fd[0]));
	}

	entry->extra = (void *)extra_fd;

	pthread_create(&t, NULL, (void *)uart_loop, (void *)entry);

	return entry;
}

static unsigned int read_usart_device(ARMUsartDevice *entry,
				unsigned int location, int num_bytes) {
	        int temp = 0;
        int num;
	int addr = location - entry->location;
        int endianess = 0;
        int i;
        int j;

        if(endianess == 0) {
                for(i = 0; i < num_bytes; i++) {
                        num = (entry->memory[addr + i] & 0xff) << (i * 8);
                        temp |= num;
                }
        } else {
                for(i = 0; i < num_bytes; i++) {
                        j = num_bytes - 1 - i;
                        num = (entry->memory[addr + i] & 0xff) << (j * 8);
                        temp |= num;
                }
        }

        return temp;
}

static void write_usart_device(ARMUsartDevice *entry, 
				unsigned int location, int num_bytes,
				int value) {
	int temp = 0;
        int num;
	int addr = location - entry->location;
        int endianess = 0;
        int i;
        int j;

        if(endianess == 0) {
                for(i = 0; i < num_bytes; i++) {
                        entry->memory[addr + i] = getbits(value, i * 8, 8);
                }
        } else {
                for(i = 0; i < num_bytes; i++) {
                        j = num_bytes - 1 - i;
                        entry->memory[addr + i] = getbits(value, j * 8, 8);
                }
        }


	if(addr == 0x001c && uart_send_enabled(entry)) {
		entry->memory[0x0014] = setbit(entry->memory[0x0014], 0, 1);
	}
}


