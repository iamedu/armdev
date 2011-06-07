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

include Makefile.inc

all: all-recursive $(EXE) 

all-recursive:
	for dir in $(DIRS); do cd $$dir; $(MAKE); cd ..; done

$(EXE): main.o utils.o interface.o
	gcc main.o utils.o interface.o instruction/*.o processor/*.o -o $(EXE) -lreadline -lpthread -llua  -lm -lconfig -lutil

utils.o: utils.c
	gcc -c utils.c $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

interface.o: interface.c
	gcc -c interface.c $(CFLAGS)

clean:
	for dir in $(DIRS); do cd $$dir; $(MAKE) clean; cd ..; done
	rm *.o armux

