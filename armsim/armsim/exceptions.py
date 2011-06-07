"""
    armsim exceptions module
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
#along with armsim.  If not, see <http://www.gnu.org/licenses/>

from armsim.processor import ProcessorMode

class ProcessorException(Exception):
    """
        Processor Exception
    """

    mode        = 0
    normal_addr = 0
    high_addr   = 0

    def preprocess(self, proc):
        proc.setStatusFlag('M', self.mode)

        proc.r14  = proc.pc
        proc.spsr = proc.cpsr
        proc.setStatusFlag('T', 0)

        if self.mode == ProcessorMode.IRQ or self.mode == ProcessorMode.FIQ:
            proc.setStatusFlag('F', 1)
        proc.setStatusFlag('I', 1)

        proc.setStatusFlag('E', proc.coprocessors['c15'].readEE())
        v = proc.coprocessors['c15'].readV()
        
        if v == 1:
            proc.pc = self.high_addr
        else:
            proc.pc = self.normal_addr

class Reset(ProcessorException):
    """
        Reset Exception
    """
    normal_addr = 0x00000000
    high_addr   = 0xFFFF0000

    mode = ProcessorMode.Supervisor

class UndefinedInstruction(ProcessorException):
    """
        When processor has a data abort
    """

    mode = ProcessorMode.Undefined
    normal_addr = 0x00000004
    high_addr   = 0xFFFF0004

class SWInterrupt(ProcessorException):
    """
        Software Interrupt
    """
    normal_addr = 0x00000008
    high_addr   = 0xFFFF0008

    mode = ProcessorMode.Supervisor

class PrefetchAbort(ProcessorException):
    """
        Prefetch abort
    """
    normal_addr = 0x0000000C
    high_addr   = 0xFFFF000C

    mode = ProcessorMode.Abort

class DataAbort(ProcessorException):
    """
        When processor has a data abort
    """

    mode = ProcessorMode.Abort
    normal_addr = 0x00000010
    high_addr   = 0xFFFF0010

class IRQInterrupt(ProcessorException):
    """
        IRQ Interrupt
    """
    normal_addr = 0x00000018
    high_addr   = 0xFFFF0018

    mode = ProcessorMode.IRQ

class FIQInterrupt(ProcessorException):
    """
        FIQ Interrupt
    """
    
    normal_addr = 0x0000001C
    high_addr   = 0xFFFF001C
    mode = ProcessorMode.FIQ

