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
from zope.interface import implements

class ARMMlaInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111000000000000011110000
    bitmask  = 0b00000000001000000000000010010000

    def execute(self, proc, inst):
        print "Ejecutaste un mla"

class ARMMulInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111000000000000011110000
    bitmask  = 0b00000000000000000000000010010000

    def execute(self, proc, inst):
        print "Ejecutaste un mul"

class ARMSmlaInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111100000000000010010000
    bitmask  = 0b00000001000000000000000010000000

    def execute(self, proc, inst):
        print "Ejecutaste un smla<x><y>"

class ARMSmlalInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111000000000000011110000
    bitmask  = 0b00000000111000000000000010010000

    def execute(self, proc, inst):
        print "Ejecutaste un smlal"

class ARMSmlalxyInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111100000000000010010000
    bitmask  = 0b00000001010000000000000010000000

    def execute(self, proc, inst):
        print "Ejecutaste un smlal<x><y>"

class ARMSmlawyInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111100000000000010110000
    bitmask  = 0b00000001001000000000000010000000

    def execute(self, proc, inst):
        print "Ejecutaste un smlaw<y>"

class ARMSmulxyInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111100000000000010010000
    bitmask  = 0b00000001011000000000000010000000

    def execute(self, proc, inst):
        print "Ejecutaste un smul<x><y>"

class ARMSmullInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111000000000000011110000
    bitmask  = 0b00000000110000000000000010010000

    def execute(self, proc, inst):
        print "Ejecutaste un smull"

class ARMSmulwyInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111100000000000010110000
    bitmask  = 0b00000001001000000000000010100000

    def execute(self, proc, inst):
        print "Ejecutaste un smulw<y>"

class ARMUmlalInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111000000000000011110000
    bitmask  = 0b00000000101000000000000010010000

    def execute(self, proc, inst):
        print "Ejecutaste un umlal"

class ARMUmullInstruction(object):
    implements(IARMInstruction)

    testmask = 0b00001111111000000000000011110000
    bitmask  = 0b00000000100000000000000010010000

    def execute(self, proc, inst):
        print "Ejecutaste un umull"

