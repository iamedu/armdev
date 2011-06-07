"""
at91sam9cp15.py

created by Eduardo Diaz

This module defines the cp15 coprocessor for the
at91sam9 microcontrollers
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
from armsim import utils
from armsim.interfaces.armcoprocessor import IARMCoprocessor
from zope.interface import implements

class AT91Sam9260CP15(object):
    implements(IARMCoprocessor)
    
    regs = {}

    def readEE(self):
        reg1 = Bitset(self.regs['c10'], 32)
        return reg1[25]

    def readV(self):
        reg1 = Bitset(self.regs['c10'], 32)
        return reg1[13]

    def __init__(self):
        self.regs['c00']  = 0 #ID Code
        self.regs['c01']  = 0 #Cache type
        self.regs['c02']  = 0 #TCM status
        self.regs['c10']  = 0 #Control
        self.regs['c20']  = 0 #TLB
        self.regs['c30']  = 0 #Domain access control
        self.regs['c40']  = 0 #Reserved
        self.regs['c50']  = 0 #Data fault status
        self.regs['c51']  = 0 #Data fault status
        self.regs['c60']  = 0 #Fault address
        self.regs['c70']  = 0 #Cache operations
        self.regs['c80']  = 0 #TLB Operations
        self.regs['c90']  = 0 #Cache lockdown
        self.regs['c91']  = 0 #TCM region
        self.regs['c100'] = 0 #TLB Lockdown
        self.regs['c110'] = 0 #Reserved
        self.regs['c120'] = 0 #Reserved
        self.regs['c130'] = 0 #FCSE PID
        self.regs['c131'] = 0 #Context ID
        self.regs['c140'] = 0 #Reserved ID
        self.regs['c150'] = 0 #Test configuration

    def readReg(self, inst):
       pass
        
    def saveReg(self, inst):
        pass
