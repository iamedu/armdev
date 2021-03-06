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


from armsim.interfaces.arminstruction import IARMInstruction
from armsim import utils
from armsim.bitset import Bitset
from zope.interface import implements

class ARMBlInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001110000000000000000000000000
    bitmask  = 0b00001010000000000000000000000000

    def execute(self, proc, inst):
        if not utils.checkCondition(proc, inst):
            return

        l = utils.getBits(inst, 24)
        signed_immed_24 = utils.getBits(inst, 0, 24)

        if l == 1:
            proc.lr = proc.pc

        branch_addr = utils.signExtend(signed_immed_24, 24, 30)
        branch_addr = branch_addr << 2
        branch_addr = utils.signValue(branch_addr)
        proc.pc += 4 + branch_addr


class ARMBlx1Instruction(object):
    implements(IARMInstruction)

    testmask = 0b11111110000000000000000000000000
    bitmask  = 0b11111010000000000000000000000000

    def execute(self, proc, inst):
        raise Exception("Thumb instruction set not implemented")

class ARMBlx2Instruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111100000000000011110000
    bitmask  = 0b00000001001000000000000000110000

    def execute(self, proc, inst):
        if not utils.checkCondition(proc, inst):
            return
        target = utils.getBits(inst, 0, 4)
        proc.lr = proc.pc
        t = utils.getBits(target, 0)
        if t:
            raise Exception("Thumb instruction set not implemented")
        proc.pc = target & 0xFFFFFFFE
            

class ARMBxInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111100000000000011110000
    bitmask  = 0b00000001001000000000000000010000

    def execute(self, proc, inst):
        if not utils.checkCondition(proc, inst):
            return
        target = utils.getBits(inst, 0, 4)
        t = utils.getBits(target, 0)
        if t:
            raise Exception("Thumb instruction set not implemented")
        proc.pc = target & 0xFFFFFFFE

