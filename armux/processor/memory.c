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
#include <armux/memory.h>
#include <stdlib.h>

ARMMem *init_memory(int size) {
	ARMMem *result = malloc(sizeof(ARMMem));
	result->size = size;
	result->entries = malloc(sizeof(ARMMemEntry *) * size);
	return result;
}

ARMMemEntry *init_phys_memory(unsigned int location, int size) {
	ARMMemEntry *entry = malloc(sizeof(ARMMemEntry));
	entry->location = location;
	entry->size = size;
	entry->type = INTERNAL;
	entry->memory = malloc(size);
	entry->read_memory  = read_phys_memory;
	entry->write_memory = write_phys_memory;
	return entry;
}

static unsigned int read_phys_memory(ARMMemEntry *entry, unsigned int location,
				int num_bytes) {
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

static void write_phys_memory(ARMMemEntry *entry, 
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
}


