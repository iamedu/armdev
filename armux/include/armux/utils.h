#ifndef _UTILS_H
#define _UTILS_H

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

#define getbit(x, y) (_get_bits(x, y, 1))
#define getbits(x, y, z) (_get_bits(x, y, z))

#define setbit(x, y, w) (_set_bits(x, y, w, 1))
#define setbits(x, y, z, w) (_set_bits(x, y, z, w))

int _get_bits(int, int, int);
int _set_bits(int, int, int, int);

int asr(int, int);
int ror(int, int);
int rol(int, int);

int sign_extend(int, int, int);

int count_set_bits(int);

int add_with_carry(int, int, int *);
int sub_with_borrow(int, int, int *);

#endif

