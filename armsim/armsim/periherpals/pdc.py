"""
usart.py

Created by Eduardo Diaz

Periherpal DMA Controller
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
from armsim.periherpals import AccessMode
from armsim.periherpals import PeriherpalRegister

class PDC(object):
    """
    This class defines the usart registers and functions
    """
    regs = {}

    def __init__(self):
        self.reset()

    def reset(self):
        self.regs[0x100] = PeriherpalRegister('PERIPH_RPR', 0)
        self.regs[0x104] = PeriherpalRegister('PERIPH_RCR', 0)
        self.regs[0x108] = PeriherpalRegister('PERIPH_TPR', 0)
        self.regs[0x10c] = PeriherpalRegister('PERIPH_TCR', 0)
        self.regs[0x110] = PeriherpalRegister('PERIPH_RNPR', 0)
        self.regs[0x114] = PeriherpalRegister('PERIPH_RNCR', 0)
        self.regs[0x118] = PeriherpalRegister('PERIPH_TNPR', 0)
        self.regs[0x11c] = PeriherpalRegister('PERIPH_TNCR', 0)
        self.regs[0x120] = PeriherpalRegister('PERIPH_PTCR', 0, AccessMode.WriteOnly)
        self.regs[0x124] = PeriherpalRegister('PERIPH_PTSR', 0, AccessMode.ReadOnly)

