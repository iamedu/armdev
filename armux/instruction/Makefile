# Copyright 2009 armux authors.
#
# This file is part of armux.
#
# armux is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# armux is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with armux.  If not, see <http://www.gnu.org/licenses/>

include ../Makefile.inc

all: branch.o instruction.o misc.o mult.o ldstr.o dp.o exception.o coprocessor.o addressing.o

branch.o: branch.c
	gcc -c branch.c $(CFLAGS)

instruction.o: instruction.c
	gcc -c instruction.c $(CFLAGS)

misc.o: misc.c
	gcc -c misc.c $(CFLAGS)

ldstr.o: ldstr.c
	gcc -c ldstr.c $(CFLAGS)

dp.o: dp.c
	gcc -c dp.c $(CFLAGS)
	
exception.o: exception.c
	gcc -c exception.c $(CFLAGS)

coprocessor.o: coprocessor.c
	gcc -c coprocessor.c $(CFLAGS)

addressing.o: addressing.c
	gcc -c addressing.c $(CFLAGS)

clean:
	rm -rf *.o
