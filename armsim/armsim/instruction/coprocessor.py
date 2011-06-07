"""
coprocessor.py

Created by Eduardo Diaz

Defines coprocessor instructions
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

class ARMCDPInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111000000000000000000010000
    bitmask  = 0b00001110000000000000000000000000

    def execute(self, proc, inst):
        print "Ejecutaste un CDP"

class ARMLDCInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001110000100000000000000000000
    bitmask  = 0b00001100000100000000000000000000

    def execute(self, proc, inst):
        print "Ejecutaste un LDC"

class ARMMCRInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111000100000000000000010000
    bitmask  = 0b00001110000000000000000000010000

    def execute(self, proc, inst):
        print "Ejecutaste un MCR"

class ARMMCRRInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111100000000000000000000
    bitmask  = 0b00001100010000000000000000000000

    def execute(self, proc, inst):
        print "Ejecutaste un MCRR"

class ARMMRCInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111000100000000000000010000
    bitmask  = 0b00001110000100000000000000010000

    def execute(self, proc, inst):
        print "Ejecutaste un MRC"

class ARMMRRCInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111100000000000000000000
    bitmask  = 0b00001100010100000000000000000000

    def execute(self, proc, inst):
        print "Ejecutaste un MRRC"

class ARMSTCInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001110000100000000000000000000
    bitmask  = 0b00001100000000000000000000000000

    def execute(self, proc, inst):
        print "Ejecutaste un STC"

