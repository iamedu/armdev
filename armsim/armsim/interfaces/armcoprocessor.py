"""
armcoprocessor.py

Created by Eduardo Diaz
On May 10, 2009

This file defines the coprocessors our ARM Processor may interact with
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

from zope.interface import Interface
from zope.interface import Attribute

class IARMCoprocessor(Interface):
    """This interface defines the ARM coprocessor"""
 
    regs = Attribute("Registers for the ARM coprocessor")

    def readReg(inst):
        """
        Reads register with inst instruction
        """

    def saveReg(inst):
        """
        Save register with inst instruction
        """

