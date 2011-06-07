"""
at91sam9memory.py

created by Eduardo Diaz
"""
#Copyright 2009 armsim authors.
#
#This file is part of armsim.
#
#armsim is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#armsim is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with armsim.  If not, see <http://www.gnu.org/licenses/>.

from armsim.bitset import Bitset
from armsim.periherpals.usart import Usart
from armsim import utils

class AT91MemoryRange(object):

    def __init__(self, init, mem):
        self.base = init
        if type(mem) == list:
            self.limit = len(mem)
        else:
            self.limit = mem.len + self.base
        self.mem = mem
        
        

class AT91Sam9Memory(object):
    memory = {}
    def __init__(self):
        memory = self.memory

        self.initMemory(0x00000000, 0x100000)

        memory[0xFFFB0000] = AT91MemoryRange(0xFFFB0000, Usart())
        #memory[0xFFFB4000] = AT91MemoryRange(0xFFFB4000, Usart())
        #memory[0xFFFB8000] = AT91MemoryRange(0xFFFB8000, Usart())

    def initMemory(self, init, size):
        memory = self.memory
        mem = [0 for i in range(size)]
        memory[init] = AT91MemoryRange(init, mem)

    def read(self, addr):
        for ind, dev in self.memory.items():
            if addr >= dev.base and addr < dev.limit:
                if type(dev.mem) == list:
                    return dev.mem[addr - dev.base]
                else:
                    return dev.mem.read(addr - dev.base)
        return 0

    def write(self, addr, value):
        value = abs(value) & 0xFFFFFFFF
        for ind, dev in self.memory.items():
            if addr >= dev.base and addr < dev.limit:
                if type(dev.mem) == list:
                    dev.mem[addr - dev.base] = value
                else:
                    dev.mem.write(addr - dev.base, value)
                break


