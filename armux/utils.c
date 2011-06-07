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

int _get_bits(int val, int start_bit, int num) {
	int bitmask = 0;
	unsigned int result;
	int i;
	for(i = 0; i < num; i++) {
		bitmask |= 1 << i;
	}
	bitmask <<= start_bit;
	result = bitmask & val;
	result >>= start_bit;
	return result;
}

int _set_bits(int val, int newval, int start_bit, int num) {
	int bitmask = 0;
	int result;
	int i;
	for(i = 0; i < num; i++) {
		bitmask |= 1 << i;
	}
	newval &= bitmask;
	bitmask <<= start_bit;
	bitmask = ~bitmask;
	val &= bitmask;
	newval <<= start_bit;
	result = val | newval;
	return result;
}

int asr(int num, int shift) {
	int sign = num & 0x80000000;
	int mask;
	int result;
	int i;

	result = num >> shift;

	if(sign) {
		mask = 0x80000000;
		result = num >> shift;
		for(i = 0; i < shift; i++) {
			result |= (mask >> i);
		}
	}

	return result;
}

int ror(int val, int x) {
	int a;
	int b;
	int c;
	int d;
	a = val;
	b = a >> x;
	c = a << (32 - x);
	d = b | c;
	return d;
}

int rol(int val, int x) {
	int a;
	int b;
	int c;
	int d;
	a = val;
	b = a << x;
	c = a >> (32 - x);
	d = b | c;
	return d;
}

int sign_extend(int num, int bits, int new_bits) {
	int mask;
	mask = 1 << (bits - 1);
	int i;
	int limit;
	if(mask & num) {
		mask = 1 << (new_bits - 1);
		limit = new_bits - bits;
		for(i = 0; i < limit; i++) {
			num |= (mask >> i);
		}
	}
	return num;
}

int count_set_bits(int num) {
	int mask = 1;
	int i;
	int count = 0;
	for(i = 0; i < 32; i++) {
		if(mask & num) {
			count++;
		}
		mask <<= 1;
	}
	return count;
}

int add_with_carry(int a, int b, int *carry) {
	int num;
	int i;
	int c = 0;
	for(i = 0; i < 32; i++) {
		num = getbit(a, i) + getbit(b, i) + c;
		if(num >= 2) {
			c    = 1;
			num -= 2;
		} else {
			c = 0;
		}
	}
	*carry = c;
	return a + b;
}

int sub_with_borrow(int a, int b, int *borrow) {
	int num;
	int substract;
	int i;
	int c = 0;
	for(i = 0; i < 32; i++) {
		substract = getbit(b, i) + c;
		num = getbit(a, i) - substract;
		if(num == -2) {
			c   = 1;
			num = 0;
		} else if(num == -1) {
			c   = 1;
			num = 1;
		} else {
			c = 0;
		}
	}
	*borrow = c;
	return a - b;
}

