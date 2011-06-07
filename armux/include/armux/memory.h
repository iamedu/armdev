#ifndef _MEMORY_H
#define _MEMORY_H

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


#define INTERNAL 0

typedef struct _ARMMemEntry {
	int type;
	unsigned int location;
	unsigned int size;
	unsigned char *memory;
	unsigned int (*read_memory)(struct _ARMMemEntry *, unsigned int, int);
	void (*write_memory)(struct _ARMMemEntry *, unsigned int, int, int);
	void *extra;
} ARMMemEntry;

typedef struct {
	int size;
	ARMMemEntry **entries;
} ARMMem;

ARMMem *init_memory(int);
ARMMemEntry *init_phys_memory(unsigned int, int);
static unsigned int read_phys_memory(ARMMemEntry *, unsigned int, int);
static void write_phys_memory(ARMMemEntry *, unsigned int, int, int);

#endif

