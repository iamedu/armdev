"""
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

from armsim.interfaces.armprocessor import IARMProcessor
from armsim.interfaces.arminstruction import IARMInstruction
from armsim.utils import testInstruction
from armsim.bitset import Bitset
from armsim import utils
from armsim import exceptions
from zope.interface import implements
from zope import component
from armsim.processor import ProcessorMode
from armsim.controllers.at91sam9cp15 import AT91Sam9260CP15
from armsim.controllers.at91sam9memory import AT91Sam9Memory
from array import array

class ARM9Processor(object):
    implements(IARMProcessor)

    regs   = {}
    __running = True
    coprocessors = {}
 
    def __init__(self):
        memory = AT91Sam9Memory()
        regs = {}
        coprocessors = {}
        coprocessors['c15'] = AT91Sam9260CP15()

        for name in IARMProcessor.names():
            if name != 'memory':
                regs[name] = 0

        self.__dict__['regs'] = regs
        self.__dict__['coprocessors'] = coprocessors
        self.__dict__['memory'] = memory

        self.reset()
  
    def halt(self):
        self.__running = False

    def printStatus(self):
        regs = self.regs
        if self.__running:
            print "Processor running at 0x%x" % self.pc
        else:
            print "Processor halted execution at 0x%x" % self.pc
        for k, v in regs.items():
            print "%s=%s" % (k, v)
   
    def reset(self):
        self.regs['r14_svc'] = 0
        self.regs['spsr_svc'] = 0
        self.regs['cpsr'] = ProcessorMode.Supervisor
        self.regs['cpsr'] |= 0b11000000

    def fetch(self):
        inst = 0
        nextAddr = self.pc
        for i in range(4):
            inst |= self.memory.read(nextAddr + i) << (i * 8)

        return inst

    def resume(self):
        self.__running = True
        self.run()

    def run(self):
        processor = self
        instructions = component.getAllUtilitiesRegisteredFor(IARMInstruction)
        instructionLog = open('ilog', 'w')

        while self.__running:
            inst = processor.fetch()
            processor.step()
            executed = False
            if inst == 0:
                break
            try:
                for instruction in instructions:
                    if testInstruction(instruction, inst):
                        instructionLog.write(str(type(instruction)) + '\n')
                        instructionLog.flush()
                        instruction.execute(processor, inst)
                        executed = True
                        break
            except exceptions.ProcessorException as ex:
                ex.preprocess(self)
                executed = True

            if not executed:
                print "Instruction not recognized %x" % inst
        self.__running = False


    def step(self):
        self.pc += 4

    def setStatusFlag(self, flag, value):
        cpsr = Bitset(self.cpsr, 32)
        if flag == 'M':
            helper = Bitset(value)
            cpsr[0:5] = helper[:]
        elif flag == 'T':
            cpsr[5] = value
        elif flag == 'F':
            cpsr[6] = value
        elif flag == 'I':
            cpsr[7] = value
        elif flag == 'A':
            cpsr[8] = value
        elif flag == 'E':
            cpsr[9] = value
        elif flag == 'GE':
            helper = Bitset(value)
            cpsr[16:20] = helper[:]
        elif flag == 'J':
            cpsr[24] = value
        elif flag == 'Q':
            cpsr[27] = value
        elif flag == 'V':
            cpsr[28] = value
        elif flag == 'C':
            cpsr[29] = value
        elif flag == 'Z':
            cpsr[30] = value
        elif flag == 'N':
            cpsr[31] = value
        self.cpsr = int(cpsr)

    def statusFlag(self, flag):
        cpsr = Bitset(self.cpsr, 32)
        if flag == 'M':
            return utils.bitsetRangeToNum(cpsr[0:5])
        elif flag == 'T':
            return int(cpsr[5])
        elif flag == 'F':
            return int(cpsr[6])
        elif flag == 'I':
            return int(cpsr[7])
        elif flag == 'A':
            return int(cpsr[8])
        elif flag == 'E':
            return int(cpsr[9])
        elif flag == 'GE':
            return utils.bitsetRangeToNum(cpsr[16:20])
        elif flag == 'J':
            return int(cpsr[24])
        elif flag == 'Q':
            return int(cpsr[27])
        elif flag == 'V':
            return int(cpsr[28])
        elif flag == 'C':
            return int(cpsr[29])
        elif flag == 'Z':
            return int(cpsr[30])
        elif flag == 'N':
            return int(cpsr[31])

    def mode(self):
        return self.regs['cpsr'] & 0x0000001F;

    def __setattr__(self, name, value):
        regs = self.__dict__['regs']

        if name == 'pc':
            self.__setattr__('r15', value)
        if name == 'lr':
            self.__setattr__('r14', value)
        if name == 'sp':
            self.__setattr__('r13', value)
    
        if self.mode() == ProcessorMode.Supervisor:
            nname = name + '_svc'
            if nname in regs:
                regs[nname] = value
    
        if self.mode() == ProcessorMode.Abort:
            nname = name + '_abt'
            if nname in regs:
                regs[nname] = value
            
        if self.mode() == ProcessorMode.Undefined:
            nname = name + '_und'
            if nname in regs:
                regs[nname] = value
    
        if self.mode() == ProcessorMode.IRQ:
            nname = name + '_irq'
            if nname in regs:
                regs[nname] = value
    
        if self.mode() == ProcessorMode.FIQ:
            nname = name + '_fiq'
            if nname in regs:
                regs[nname] = value
    
        if name in regs:
            regs[name] = value
        
        object.__setattr__(self, name, value)

    def __getattr__(self, name):
        if name == 'pc':
            return self.__getattr__('r15')
        if name == 'lr':
            return self.__getattr__('r14')
        if name == 'sp':
            return self.__getattr__('r13')
        if name == '__members__':
            return self.regs.keys() + ['pc', 'lr', 'sp']
        if self.mode() == ProcessorMode.Supervisor:
            nname = name + '_svc'
            if nname in self.regs:
                return self.regs[nname]

        if self.mode() == ProcessorMode.Abort:
            nname = name + '_abt'
            if nname in self.regs:
                return self.regs[nname]
            
        if self.mode() == ProcessorMode.Undefined:
            nname = name + '_und'
            if nname in self.regs:
                return self.regs[nname]

        if self.mode() == ProcessorMode.IRQ:
            nname = name + '_irq'
            if nname in self.regs:
                return self.regs[nname]

        if self.mode() == ProcessorMode.FIQ:
            nname = name + '_fiq'
            if nname in self.regs:
                return self.regs[nname]

        if name in self.regs:
            return self.regs[name]
        
        #raise AttributeException('no such attribute ' + name)
        return self.__dict__[name]

    def saveAddr(self, address, value, num_bytes=4, endianess='L'):
        nextAddr = address

        if(endianess == 'L'):
            for i in range(num_bytes):
                self.memory.write(nextAddr + i, utils.getBits(value, i * 8, 8))
        else:
            for i in range(num_bytes):
                j = num_bytes - 1 - i
                self.memory.write(nextAddr + i, utils.getBits(value, j * 8, 8))

    
    def readAddr(self, address, num_bytes=4):
        location = 0
        nextAddr = address
 
        endianess = self.coprocessors['c15'].readEE()

        if(endianess == 0):
            for i in range(num_bytes):
                location |= self.memory.read(nextAddr + i)<< (i * 8)
        else:
            for i in range(num_bytes):
                j = num_bytes - 1 - i
                location |= self.memory.read(nextAddr + i) << (j * 8)

        return location
        

